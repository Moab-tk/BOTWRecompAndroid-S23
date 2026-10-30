// (S23) Frame generation: Lossless Scaling's, through libbloodframe.so (bb_lsfg.h), with the player's own Lossless.dll
// (imported in Settings > Files; never part of the app). vulkan/framegen.c, called by device.c's vk_frame_end.
#pragma once
#include <stdbool.h>
#include <stdint.h>
#include "vk.h"

#define FG_MAX 2  // generated frames per real one (3x)

bool fg_dll_present(void);          // the player's Lossless.dll is imported
const char *fg_status(void);        // for Settings: why generation stopped ("" when nothing went wrong)
bool fg_swapchain_wanted(void);     // the window needs what generated frames take (FIFO, more images, transfers)
// A real frame is starting its way out (render thread). game_frame: a paced frame of the game.
// Returns how many to generate (0: history only), or -1: this frame goes the normal way (off, starting, busy).
int fg_frame_start(VkExtent2D extent, bool game_frame);
void fg_copy_in(VkCommandBuffer cb, VkImage window_image, VkExtent2D extent);  // (the image in TRANSFER_SRC layout)
VkSemaphore fg_in_semaphore(void);  // signalled by the submission holding fg_copy_in
int fg_run(int gens, int ready_fd[FG_MAX]);  // after that submission. Generated frames, or -1 (generation ended itself)
void fg_copy_out(VkCommandBuffer cb, int i, VkImage window_image, VkExtent2D extent);  // (ends in PRESENT_SRC)
void fg_out_used(uint64_t seq);     // the submission reading the outputs
