// (S23) Frame generation on the render thread, see framegen.h. Each real frame is copied into one of two shared images
// (AHardwareBuffers) on its way to the window, libbloodframe computes the frames between it and the one before on a
// Vulkan device of its own, and device.c shows them, each at its time, ahead of the real one.
// Rules: nothing here may stop the game. The library starts on a thread of its own (it compiles its shaders); a frame
// that finds it still busy just goes the normal way, without waiting; any failure ends generation and says why in
// Settings. libbloodframe.so is only opened when generation is on, so with it off nothing of this runs.
#ifdef __ANDROID__
#include <SDL3/SDL_system.h>
#include <android/hardware_buffer.h>
#include <dlfcn.h>
#include <poll.h>
#include <pthread.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "../../framepace.h"
#include "../../hle.h"
#include "../../platform.h"
#include "../../settings.h"
#include "bb_lsfg.h"
#include "framegen.h"

#define FG_FORMAT VK_FORMAT_R8G8B8A8_UNORM  // (the shared images; blits take the window's BGRA to it and back)
#define AHB_FORMAT AHARDWAREBUFFER_FORMAT_R8G8B8A8_UNORM
#define GAP_NS 100000000ull                 // (a longer gap between real frames: nothing to interpolate, a load or a stall)

extern void vk_wait_seq(uint64_t seq);

enum { FG_OFF, FG_STARTING, FG_READY, FG_FAILED };
static _Atomic int g_state;

static struct {
    int (*init)(const BbLsfgConfig *, BbLsfgInfo *, char *, size_t);
    int (*create_context)(struct AHardwareBuffer *, struct AHardwareBuffer *, struct AHardwareBuffer *const *, uint32_t,
                          uint32_t, uint32_t, int32_t, char *, size_t);
    int (*present)(int, int, uint32_t, BbLsfgPresent *, char *, size_t);
    int (*wait)(int, uint64_t);
    void (*destroy_context)(int);
    void (*shutdown)(void);
    int (*shader_set)(char *, size_t);
    int (*diagnostics)(char *, size_t);
} bb;

typedef struct { AHardwareBuffer *ahb; VkImage image; VkDeviceMemory mem; } Shared;
static struct {
    uint32_t w, h;
    int key;            // (the settings this context was made for: gens | model << 4)
    int gens, ctx;
    Shared in[2], out[FG_MAX];
    VkSemaphore in_sem;
    uint64_t n;         // real frames handed over: which input is next
    int batch_fd;       // the last batch's end (sync file), -1: none
    uint64_t out_seq;   // the submission reading the outputs
    uint64_t last_ns;   // the last real frame
    uint64_t shown, skipped;
} F = {.batch_fd = -1};
static int g_failed_key = -1;
static char g_status[256];

static const char *dll_path(void) {
    static char p[1100];
    if (!p[0]) {
        const char *in = SDL_GetAndroidInternalStoragePath();
        if (in) snprintf(p, sizeof p, "%s/lossless/Lossless.dll", in);
    }
    return p;
}

bool fg_dll_present(void) {
    struct stat st;
    return dll_path()[0] && stat(dll_path(), &st) == 0 && st.st_size > 0;
}

const char *fg_status(void) { return g_status; }

static int wanted_gens(void) {
    static int forced = -2;  // LARECOMP_FRAMEGEN=2 or 3: 2x, 3x over the setting; 0: off
    if (forced == -2) forced = getenv("LARECOMP_FRAMEGEN") ? atoi(getenv("LARECOMP_FRAMEGEN")) : -1;
    int gens = forced >= 0 ? (forced > 1 ? forced - 1 : 0) : g_settings.framegen;
    if (gens > FG_MAX) gens = FG_MAX;
    return gens > 0 && g_vk.framegen_ext && g_vk.display_timing && fg_dll_present() ? gens : 0;
}
static int wanted_key(int gens) { return gens | (g_settings.framegen_model ? 1 << 4 : 0); }

bool fg_swapchain_wanted(void) {
    int gens = wanted_gens();
    return gens > 0 && !(atomic_load(&g_state) == FG_FAILED && g_failed_key == wanted_key(gens));
}

static bool load_library(char *err, size_t n) {
    if (bb.init) return true;
    const char *dir = getenv("LARECOMP_NATIVE_LIB_DIR");
    char path[1100];
    snprintf(path, sizeof path, "%s/libbloodframe.so", dir ? dir : ".");
    void *lib = dlopen(path, RTLD_NOW | RTLD_LOCAL);
    if (!lib) {
        LOG("[fg] %s\n", dlerror());
        snprintf(err, n, "this version has no frame generation library");
        return false;
    }
#define SYM(field, name) *(void **)&bb.field = dlsym(lib, name)
    SYM(init, "bb_lsfg_init");
    SYM(create_context, "bb_lsfg_create_context");
    SYM(present, "bb_lsfg_present");
    SYM(wait, "bb_lsfg_wait");
    SYM(destroy_context, "bb_lsfg_destroy_context");
    SYM(shutdown, "bb_lsfg_shutdown");
    SYM(shader_set, "bb_lsfg_shader_set");
    SYM(diagnostics, "bb_lsfg_diagnostics");
#undef SYM
    if (bb.init && bb.create_context && bb.present && bb.wait && bb.destroy_context && bb.shutdown && bb.shader_set &&
        bb.diagnostics) return true;
    bb.init = NULL;
    snprintf(err, n, "the frame generation library is incomplete");
    return false;
}

// A shared image: the AHardwareBuffer and its VkImage on our device
static bool make_shared(Shared *s, uint64_t ahb_usage, VkImageUsageFlags usage) {
    AHardwareBuffer_Desc d = {.width = F.w, .height = F.h, .layers = 1, .format = AHB_FORMAT, .usage = ahb_usage};
    if (AHardwareBuffer_allocate(&d, &s->ahb)) {
        LOG("[fg] no shared image %ux%u (usage %#llx)\n", F.w, F.h, (unsigned long long)ahb_usage);
        return false;
    }
    VkAndroidHardwareBufferFormatPropertiesANDROID fp = {.sType = VK_STRUCTURE_TYPE_ANDROID_HARDWARE_BUFFER_FORMAT_PROPERTIES_ANDROID};
    VkAndroidHardwareBufferPropertiesANDROID p = {.sType = VK_STRUCTURE_TYPE_ANDROID_HARDWARE_BUFFER_PROPERTIES_ANDROID, .pNext = &fp};
    if (vkGetAndroidHardwareBufferPropertiesANDROID(g_vk.dev, s->ahb, &p) != VK_SUCCESS || !p.memoryTypeBits) return false;
    VkExternalMemoryImageCreateInfo ext = {.sType = VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMAGE_CREATE_INFO,
                                           .handleTypes = VK_EXTERNAL_MEMORY_HANDLE_TYPE_ANDROID_HARDWARE_BUFFER_BIT_ANDROID};
    VkImageCreateInfo ci = {.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO, .pNext = &ext, .imageType = VK_IMAGE_TYPE_2D,
                            .format = FG_FORMAT, .extent = {F.w, F.h, 1}, .mipLevels = 1, .arrayLayers = 1,
                            .samples = VK_SAMPLE_COUNT_1_BIT, .tiling = VK_IMAGE_TILING_OPTIMAL, .usage = usage,
                            .sharingMode = VK_SHARING_MODE_EXCLUSIVE, .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED};
    if (vkCreateImage(g_vk.dev, &ci, NULL, &s->image) != VK_SUCCESS) return false;
    VkImportAndroidHardwareBufferInfoANDROID imp = {.sType = VK_STRUCTURE_TYPE_IMPORT_ANDROID_HARDWARE_BUFFER_INFO_ANDROID, .buffer = s->ahb};
    VkMemoryDedicatedAllocateInfo ded = {.sType = VK_STRUCTURE_TYPE_MEMORY_DEDICATED_ALLOCATE_INFO, .pNext = &imp, .image = s->image};
    VkMemoryAllocateInfo ai = {.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO, .pNext = &ded, .allocationSize = p.allocationSize,
                               .memoryTypeIndex = (uint32_t)__builtin_ctz(p.memoryTypeBits)};
    return vkAllocateMemory(g_vk.dev, &ai, NULL, &s->mem) == VK_SUCCESS &&
           vkBindImageMemory(g_vk.dev, s->image, s->mem, 0) == VK_SUCCESS;
}

static void free_shared(Shared *s) {
    if (s->image) vkDestroyImage(g_vk.dev, s->image, NULL);
    if (s->mem) vkFreeMemory(g_vk.dev, s->mem, NULL);
    if (s->ahb) AHardwareBuffer_release(s->ahb);
    memset(s, 0, sizeof *s);
}

static void free_all(void) {
    for (int i = 0; i < 2; i++) free_shared(&F.in[i]);
    for (int i = 0; i < FG_MAX; i++) free_shared(&F.out[i]);
    if (F.batch_fd >= 0) close(F.batch_fd);
    F.batch_fd = -1;
    F.n = F.out_seq = F.last_ns = 0;
}

static void fail(const char *why) {
    LOG("[fg] off: %s\n", why);
    if (why != g_status) snprintf(g_status, sizeof g_status, "%s", why);
    g_failed_key = F.key;
    atomic_store(&g_state, FG_FAILED);
}

// The slow start, off the render thread: shaders from the Lossless.dll, the device, the context
static void *start_thread(void *arg) {
    (void)arg;
    char err[256] = "";
    if (!load_library(err, sizeof err)) {
        fail(err);
        return NULL;
    }
    VkPhysicalDeviceIDProperties id = {.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ID_PROPERTIES};
    VkPhysicalDeviceProperties2 pr = {.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2, .pNext = &id};
    vkGetPhysicalDeviceProperties2(g_vk.phys, &pr);
    bool quality = (F.key >> 4) != 0;
    BbLsfgConfig c = {.vk_get_instance_proc_addr = (void *)vkGetInstanceProcAddr, .dll_path = dll_path(),
                      .flow_scale = quality ? 1.0f : 0.5f, .performance = !quality, .generation_count = F.gens,
                      .shared_format = (int32_t)FG_FORMAT, .hdr = 0, .fp16 = 1};
    memcpy(c.device_uuid, id.deviceUUID, VK_UUID_SIZE);
    memcpy(c.driver_uuid, id.driverUUID, VK_UUID_SIZE);
    BbLsfgInfo info = {0};
    uint64_t t0 = plat_now_ns();
    if (bb.init(&c, &info, err, sizeof err)) {
        fail(err[0] ? err : "the frame generation library didn't start");
        return NULL;
    }
    if (!info.sync_fd_ok) {
        bb.shutdown();
        fail("this driver can't share sync files with the frame generation library");
        return NULL;
    }
    struct AHardwareBuffer *outs[FG_MAX] = {0};
    bool ok = make_shared(&F.in[0], info.input_ahb_usage, VK_IMAGE_USAGE_TRANSFER_DST_BIT) &&
              make_shared(&F.in[1], info.input_ahb_usage, VK_IMAGE_USAGE_TRANSFER_DST_BIT);
    for (int i = 0; ok && i < F.gens; i++) {
        ok = make_shared(&F.out[i], info.output_ahb_usage, VK_IMAGE_USAGE_TRANSFER_SRC_BIT);
        outs[i] = F.out[i].ahb;
    }
    if (ok && !F.in_sem) {
        VkExportSemaphoreCreateInfo ex = {.sType = VK_STRUCTURE_TYPE_EXPORT_SEMAPHORE_CREATE_INFO,
                                          .handleTypes = VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_SYNC_FD_BIT};
        VkSemaphoreCreateInfo si = {.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO, .pNext = &ex};
        ok = vkCreateSemaphore(g_vk.dev, &si, NULL, &F.in_sem) == VK_SUCCESS;
    }
    if (ok) {
        F.ctx = bb.create_context(F.in[0].ahb, F.in[1].ahb, outs, (uint32_t)F.gens, F.w, F.h, (int32_t)FG_FORMAT, err, sizeof err);
        ok = F.ctx >= 0;
    }
    if (!ok) {
        free_all();
        bb.shutdown();
        fail(err[0] ? err : "the shared images couldn't be made");
        return NULL;
    }
    char set[256] = "", diag[768] = "";
    int which = bb.shader_set(set, sizeof set);
    bb.diagnostics(diag, sizeof diag);
    LOG("[fg] ready in %.1f s, %ux%u, %d generated per real frame, shaders %d (%s)\n", (plat_now_ns() - t0) / 1e9, F.w, F.h,
        F.gens, which, set);
    LOG("[fg] %s\n", diag);
    g_status[0] = 0;
    atomic_store(&g_state, FG_READY);
    return NULL;
}

static void stop(void) {  // (render thread, FG_READY)
    bb.wait(F.ctx, 2000000000ull);
    bb.destroy_context(F.ctx);
    bb.shutdown();
    if (F.out_seq) vk_wait_seq(F.out_seq);
    free_all();
    atomic_store(&g_state, FG_OFF);
    LOG("[fg] stopped: %llu generated frames, %llu real frames found it busy\n", (unsigned long long)F.shown,
        (unsigned long long)F.skipped);
}

static bool seq_done(uint64_t seq) {
    uint64_t v = 0;
    return !seq || (vkGetSemaphoreCounterValue(g_vk.dev, g_vk.timeline, &v) == VK_SUCCESS && v >= seq);
}

int fg_frame_start(VkExtent2D extent, bool gens_ok) {
    int want = wanted_gens(), st = atomic_load(&g_state);
    if (!want) {
        if (st == FG_READY) stop();
        if (st == FG_FAILED) atomic_store(&g_state, FG_OFF), g_status[0] = 0;
        return -1;
    }
    int key = wanted_key(want);
    if (st == FG_FAILED) {
        if (key == g_failed_key) return -1;  // (a changed setting tries again)
        atomic_store(&g_state, st = FG_OFF);
        g_status[0] = 0;
    }
    if (st == FG_STARTING) return -1;
    if (st == FG_READY && (F.w != extent.width || F.h != extent.height || F.key != key)) {
        stop();
        return -1;
    }
    if (st == FG_OFF) {
        F.w = extent.width, F.h = extent.height, F.key = key, F.gens = want;
        F.shown = F.skipped = 0;
        atomic_store(&g_state, FG_STARTING);
        pthread_t t;
        if (pthread_create(&t, NULL, start_thread, NULL)) fail("the frame generation thread didn't start");
        else pthread_detach(t);
        return -1;
    }
    if (F.batch_fd >= 0) {  // (the last batch still at work: its inputs are in use)
        struct pollfd p = {.fd = F.batch_fd, .events = POLLIN};
        if (poll(&p, 1, 0) <= 0) {
            F.skipped++;
            return -1;
        }
        close(F.batch_fd);
        F.batch_fd = -1;
    }
    if (!seq_done(F.out_seq)) {  // (the outputs still being read)
        F.skipped++;
        return -1;
    }
    uint64_t now = plat_now_ns();
    bool gap = F.last_ns && now - F.last_ns > GAP_NS;
    F.last_ns = now;
    return gens_ok && !gap && !framepace_in_menu() && !framepace_on_title() ? F.gens : 0;
}

static VkImageMemoryBarrier2 barrier(VkImage img, VkImageLayout from, VkImageLayout to, uint32_t src_q, uint32_t dst_q,
                                     VkAccessFlags2 src, VkAccessFlags2 dst) {
    return (VkImageMemoryBarrier2){.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2,
                                   .srcStageMask = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT, .srcAccessMask = src,
                                   .dstStageMask = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT, .dstAccessMask = dst,
                                   .oldLayout = from, .newLayout = to, .srcQueueFamilyIndex = src_q, .dstQueueFamilyIndex = dst_q,
                                   .image = img, .subresourceRange = {VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1}};
}
static void barriers(VkCommandBuffer cb, const VkImageMemoryBarrier2 *b, uint32_t n) {
    VkDependencyInfo di = {.sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO, .imageMemoryBarrierCount = n, .pImageMemoryBarriers = b};
    vkCmdPipelineBarrier2(cb, &di);
}
static void blit(VkCommandBuffer cb, VkImage src, VkImage dst, VkExtent2D e) {
    VkImageBlit r = {.srcSubresource = {VK_IMAGE_ASPECT_COLOR_BIT, 0, 0, 1},
                     .srcOffsets = {{0, 0, 0}, {(int32_t)e.width, (int32_t)e.height, 1}},
                     .dstSubresource = {VK_IMAGE_ASPECT_COLOR_BIT, 0, 0, 1},
                     .dstOffsets = {{0, 0, 0}, {(int32_t)e.width, (int32_t)e.height, 1}}};
    vkCmdBlitImage(cb, src, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, dst, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &r, VK_FILTER_NEAREST);
}

// Into an input, handed to the library's device: EXTERNAL -> our queue -> EXTERNAL, in GENERAL between uses
static void copy_into(VkCommandBuffer cb, Shared *s, VkImage window_image, VkExtent2D e, bool first_use) {
    VkImageMemoryBarrier2 b = barrier(s->image, first_use ? VK_IMAGE_LAYOUT_UNDEFINED : VK_IMAGE_LAYOUT_GENERAL,
                                      VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_QUEUE_FAMILY_EXTERNAL, g_vk.qfam, 0,
                                      VK_ACCESS_2_TRANSFER_WRITE_BIT);
    barriers(cb, &b, 1);
    blit(cb, window_image, s->image, e);
    b = barrier(s->image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_GENERAL, g_vk.qfam, VK_QUEUE_FAMILY_EXTERNAL,
                VK_ACCESS_2_TRANSFER_WRITE_BIT, 0);
    barriers(cb, &b, 1);
}

void fg_copy_in(VkCommandBuffer cb, VkImage window_image, VkExtent2D e) {
    copy_into(cb, &F.in[F.n & 1], window_image, e, F.n < 2);
    if (!F.n) copy_into(cb, &F.in[1], window_image, e, true);  // (the first frame fills the pair: it has no neighbour yet)
}

VkSemaphore fg_in_semaphore(void) { return F.in_sem; }

int fg_run(int gens, int ready_fd[FG_MAX]) {
    char err[256] = "";
    VkSemaphoreGetFdInfoKHR gi = {.sType = VK_STRUCTURE_TYPE_SEMAPHORE_GET_FD_INFO_KHR, .semaphore = F.in_sem,
                                  .handleType = VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_SYNC_FD_BIT};
    int fd = -1;
    BbLsfgPresent out;
    bool ok = vkGetSemaphoreFdKHR(g_vk.dev, &gi, &fd) == VK_SUCCESS;
    if (ok) ok = bb.present(F.ctx, fd, (uint32_t)gens, &out, err, sizeof err) == 0;
    if (!ok) {
        snprintf(g_status, sizeof g_status, "%s", err[0] ? err : "a frame couldn't go to the frame generation library");
        stop();
        fail(g_status);
        return -1;
    }
    F.n++;
    F.batch_fd = out.batch_complete_fd;
    for (int i = 0; i < gens; i++) ready_fd[i] = out.gpu_synced ? out.out_ready_fd[i] : -1;
    F.shown += (uint64_t)gens;
    return gens;
}

void fg_copy_out(VkCommandBuffer cb, int i, VkImage window_image, VkExtent2D e) {
    VkImageMemoryBarrier2 in[2] = {
        barrier(F.out[i].image, VK_IMAGE_LAYOUT_GENERAL, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, VK_QUEUE_FAMILY_EXTERNAL, g_vk.qfam, 0,
                VK_ACCESS_2_TRANSFER_READ_BIT),
        barrier(window_image, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_QUEUE_FAMILY_IGNORED,
                VK_QUEUE_FAMILY_IGNORED, 0, VK_ACCESS_2_TRANSFER_WRITE_BIT)};
    barriers(cb, in, 2);
    blit(cb, F.out[i].image, window_image, e);
    VkImageMemoryBarrier2 back[2] = {
        barrier(F.out[i].image, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, VK_IMAGE_LAYOUT_GENERAL, g_vk.qfam, VK_QUEUE_FAMILY_EXTERNAL,
                VK_ACCESS_2_TRANSFER_READ_BIT, 0),
        barrier(window_image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, VK_QUEUE_FAMILY_IGNORED,
                VK_QUEUE_FAMILY_IGNORED, VK_ACCESS_2_TRANSFER_WRITE_BIT, VK_ACCESS_2_MEMORY_READ_BIT)};
    barriers(cb, back, 2);
}

void fg_out_used(uint64_t seq) { F.out_seq = seq; }
#endif
