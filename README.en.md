# BOTW S23

[Português](README.md) | **English**

An **unofficial** modification of [BOTWRecompAndroid](https://github.com/mamcjr/BOTWRecompAndroid), tuned for the
**Samsung Galaxy S23 Ultra** (Snapdragon 8 Gen 2, Adreno 740).

> [!IMPORTANT]
> **The original project belongs to [mamcjr](https://github.com/mamcjr), creator of
> [BOTWRecompAndroid](https://github.com/mamcjr/BOTWRecompAndroid), built on the LAS Recomp by
> [peiikai](https://github.com/peiikai). All credit for the project is theirs.**
>
> This version is a personal modification made by someone else, with help from AI. mamcjr gave permission to publish it,
> but took no part in these changes, didn't test them and isn't responsible for them.

> [!CAUTION]
> **A problem with this version? Open an [issue here](https://github.com/Moab-tk/BOTWRecompAndroid-S23/issues). Never take these complaints to the original project.**
> A bug here may have been created by these changes and may not exist in the original. It may work well on the tester's
> phone and badly on yours.

> [!NOTE]
> Don't take any of this too seriously. If it doesn't work on your phone, just leave it and download the version you like
> best.

> [!WARNING]
> **The test phone is modified.** It's a 12 GB S23 Ultra, already a strong phone, with an overclock, with the system's
> thermal limiter turned off by third-party tools, with other changes that slightly improve performance, and with a
> cooler. No number on this page is a promise for a regular phone. In my personal test, this version gave a real gain in
> performance and smoothness on that phone. How it does on unmodified phones is for other people to test.

The project's original text, with all the technical details, is in [README-ORIGINAL.md](README-ORIGINAL.md). The list of
changes is in [MUDANCAS-S23.md](MUDANCAS-S23.md) (in Portuguese).

## No game files

**No game files are included.** You need your own legally obtained dump of *Breath of the Wild* (`exefs` and `romfs`,
extracted). No instructions on how to get it will be given.

## What's different in this version

- **Built for the S23's processor**, without the instructions it doesn't have.
- **Installs next to the original:** the package is different (`com.botwrecomp.android.s23`), so one doesn't replace the
  other.
- **Based on version 0.3.1 of the original**, with mamcjr's fixes up to it, such as the crashes with Magnesis, Stasis
  and the Slate's camera, the arrow button and the gyro like the Switch's screen.
- **Two versions:** the S23 one, built for the Snapdragon 8 Gen 2's processor, and the Universal one, for any arm64 phone
  with Vulkan. The Universal one is experimental: it was only tested on the S23.
- **Fewer missing objects when entering areas:** the app remembers the pipelines the game used and builds them again before
  the first draw. Entering the world, skipped draws went from 5,780 down to 132.
- **Five Turnip drivers in the app**, in Settings > Files > Vulkan driver. The two tested ones show as Recommended, and
  the three newer ones show as not tested on this game.
- **Steady frames at 30 FPS:** the screen stays at 60 Hz and each frame follows its real rhythm. In the measurements, 97%
  of the frames showed on time, with none dropped.
- **Recommended settings with one tap:** the ones tested on the S23 Ultra, and a lighter option for the S23, S23+ and
  weaker phones.
- **Saved settings:** 8 blocks to keep everything you set and go back when a test makes things worse.
- **A larger interface, easier to tap:** text size choice, long names that slide, options in cards.
- **Higher touch sensitivity:** the camera drag goes up to 800% and the bow aim, in the icon layout, up to 400%.
- **Aim by dragging (experimental):** with the bow held and motion controls on, a drag turns the aim as the phone
  turning would, faster than the stick's top speed.
- **Motion with the sticks (new):** for the shrines' motion puzzles. In System > Controls: the left stick tilts the
  controller and the right one turns it; gentle through most of the travel, the full motion only at the edge. With
  "Quick button on the screen", a button you can drag turns it on and off without opening the menu. In the author's
  tests, those shrines were much easier this way than tilting the phone, but it's just one more option: play the way
  you like best.
- **Less waiting for the GPU:** small copies the game asks for are made by the GPU itself (from mamcjr's TOTKDroid).
- **Less risk of a hang in long sessions**, with larger shader tables.

## Installing

You need Android 11 or newer, an arm64 phone with Vulkan and about 30 GB free for each version of the game.

1. Download the APK from the **Releases** tab on this page and install it.
2. Open it, go to **Set up game files** and pick the folder with your `exefs` and `romfs`.
3. Wait for it to finish. The first time, the phone may take a while and get warm.
4. On the start screen, open **Saved settings** and tap one of the recommended options.
5. Confirm. The app restarts and the game is ready to play.

When updating from an earlier version of this modification, just install over it: saves and settings stay.

## Recommended settings

These are the values the buttons apply. The lighter option wasn't tested on the S23, the S23+ or weaker phones.

| Option | S23 Ultra | S23, S23+ and weaker |
|---|---|---|
| Frame rate limit | 30 FPS | 30 FPS |
| Internal resolution | 1x | 75% |
| Output resolution | 1080 lines | 900 lines |

Both use the values below:

| Option | Value |
|---|---|
| Upscaler | FSR 1 |
| Anti-aliasing | Off |
| Game code | Native |
| Presentation | FIFO |
| Steady frames at 30 FPS | On |
| Driver compatibility | Automatic (on for the Adreno 740) |
| Driver | The Turnip recommended for your phone |

The screen shape, sound, controls, mods and saves don't change.

## Which driver to use

All are Mesa builds by [The412Banner](https://github.com/The412Banner/Banners-Turnip). The 10/25 ones were used in the
tests. The 11/01 ones are automated builds: their author warns they weren't tested on a device, and they weren't tested on
this game.

| Your phone | Driver | Status |
|---|---|---|
| Galaxy S23, with One UI | `Turnip-v27.0.0-20261025-r5-8G2-OneUI` | Recommended |
| Other Snapdragon 8 Gen 2 | `Turnip-v27.0.0-20261025-r5` | Recommended |
| Galaxy S23, with One UI | `Turnip-v27.0.0-20261101-r4-8G2-OneUI` | Newer, not tested |
| Other Adreno 6xx and 7xx GPUs | `Turnip-v27.0.0-20261101-r4` | Newer, not tested |
| Adreno 8xx (Snapdragon 8 Elite) | `Turnip-v27.0.0-20261101-r4-A8xx` | Experimental, not tested |

The One UI one may make the screen flicker on phones that aren't Samsung. Nothing here was tested on other devices.

## Measured performance

These numbers come from a single **modified** phone and are no promise: a 12 GB S23 Ultra with an overclock and other
changes, game version 1.8.2, native code, 30 FPS, 1x resolution. Up to b7, the output was 900 lines; on b8, 1080, with the
original aspect ratio.

| Measurement | Average FPS | Samples below 29 FPS | Spikes of 100 ms or more |
|---|---:|---:|---:|
| b6: 10 minutes in varied places | 29.9 | 6 of 290 | 1 |
| A b7 stage: 11 minutes in areas never visited | 29.9 | 5 of 341 | 5 |
| b8: 4 and a half minutes | 29.9 | 6 of 120 | 4 |

On b9, standing still at the same spot and in the same save as b8, with the phone charging: 29.9 FPS against 29.8; 93.7% of
frames on time against 90.8%; and 84.4 °C on the processor against 86.8 °C.

On b10, two sessions in a row, in the same save and along the same route, with the temperature control on:

| | Only recording | Building ahead |
|---|---:|---:|
| Average FPS | 29.8 | 29.7 |
| Peak entering the world | 305 ms | 213 ms |
| Skipped draws entering the world | 5,780 | 132 |
| Skipped draws per minute | 461 | 106 |

The chip stayed between 70 and 76 °C and the battery between 29 and 31 °C. The FPS drop right after entering the world,
seen in this measurement, was fixed after it, and the fix wasn't measured.

Each sample covers 2 seconds of play. Average FPS doesn't tell everything: it shows how many frames went out, not whether
they reached the screen at a steady pace. This was measured by the system itself, on every frame shown:

| On the screen | b7 | b8 |
|---|---:|---:|
| Frames on time | 93.3% | 97.2% |
| Frames dropped per second | 1.0 | 0 |
| Late frames per second | 1.0 | 0.45 |
| Pace variation | 8.6 ms | 4.6 ms |

**What didn't work:** 40 FPS (36.8 on average, with the GPU slowing down from heat and the processor at 88 °C) and the
game's own shorter draw distance on the whole map (3.5% fewer draws at the same spot, with the same GPU use).

> [!WARNING]
> These sessions were played with an **overclock**, a **cooler on the phone** and the **system's thermal limiter turned off
> by the phone's owner**, through third-party tools. None of that is part of the app, and none of it is recommended here:
> making those changes is at your own risk. The chip went over 80 °C. Without them, expect less performance.

## Known problems

- **b13 played only a little:** one motion shrine and a quick performance test. If something gets worse, go back to
  b11. Aim by dragging comes off, and its direction wasn't checked yet.
- **60 FPS:** on the S23 Ultra, the 60 mode stayed at 30 to 32 FPS (each frame took 33 to 41 ms), with the chip cool.
  Use 30.
- **40 FPS:** the original's new option needs a 120 Hz screen and more heat. On the S23 Ultra, 40 FPS didn't hold in
  earlier tests.
- **Vertical walls on the terrain ("curtains"):** mamcjr fixed this defect in 0.2.10, and the fix is here. It wasn't tested
  deeply on the S23 yet. If it happens, load a later save.
- **Stutter in new areas:** on the first visit, a shader may take 250 to 300 ms to get ready. After that it stays on the
  phone, so later visits tend to be lighter.
- **Building ahead:** the first session after installing a new version only records the pipelines. The gain shows from
  the second one on. Right after entering the world, this building may still take some of the processor.
- **Universal version:** only tested on the S23. On other phones, nothing was checked.
- **Heat:** even with a cooler, the chip went over 70 °C and Android marked the phone as very hot. The temperature control
  lowered the image in steps, as it should.
- **GPU stuck at a low clock:** in some sessions the system lowered the GPU from 719 to about 300 MHz and only let go when
  the game closed, even with the chip at 60 °C. Both times it was measured, the tool that turns off the limiter wasn't
  running. If the game suddenly gets slow, close it and open it again.
- **The S23 and S23+ weren't tested.** On a 12 GB phone the game took about 5 GB of RAM. Turning off the game's memory on
  the GPU, in the compatibility options, saved about 1 GB in a short measurement, but it ran hotter and less evenly, and
  the game closed by itself once, with a failure of unknown cause.
- **Tested on one phone only.** On another device, everything may be different.
- **Screen shape:** there's a report of a defect in full screen and in 16:9, with no cause found yet.
- **Frame generation (Lossless Scaling):** it was tested and removed, because on the S23 real frames dropped to 15 to 23
  FPS. This version doesn't have that option.

## Test options

On the start screen, in Settings > Video > Tests, there are options that come turned off: keep the GPU awake, presentation
mode, shader build threads, anisotropic filtering and Turnip mode. Test one at a time and save a block first. **Keep the
GPU awake** had no proven gain and, if the system force-closes the app, it may stay on until you open the app again or
restart the phone.

## Support, if you want

If this version worked for you and you'd like to help with the costs, such as Claude's tokens, voluntary help is welcome.

Donating is optional and gives no benefit: no features, priority, support or special version. It goes to Moab, the author
of this modification, not to mamcjr, peiikai or Nintendo. To support the original project, use the **Sponsor** button on
[mamcjr's repository](https://github.com/mamcjr/BOTWRecompAndroid).

Pix (random key): `5eb148c4-81dc-47cd-b2cc-b3171d3c06ab`

## Building

The steps are the original project's, in [README-ORIGINAL.md](README-ORIGINAL.md). The release uses its own key, kept
outside the repository in `~/.botwrecompandroid/keystore.properties`. Without it, build the debug version.

## Credits

- **[mamcjr](https://github.com/mamcjr)**, for [BOTWRecompAndroid](https://github.com/mamcjr/BOTWRecompAndroid) and
  [LASRecompAndroid](https://github.com/mamcjr/LASRecompAndroid): this modification exists because of that work.
- **[peiikai](https://github.com/peiikai)**, for [LAS Recomp](https://github.com/peiikai/LASRecomp) (MIT license), the
  recompiler and engine it all starts from.
- [Revivedx](https://github.com/Revivedx), for [SavageWindRecomp](https://github.com/Revivedx/SavageWindRecomp);
  [Nycolazs](https://github.com/Nycolazs), for LASRecomp-Android-Plus; the [zeldaret/botw](https://github.com/zeldaret/botw)
  decompilation and [open-ead/sead](https://github.com/open-ead/sead).
- [tib-kpl](https://github.com/tib-kpl/BOTWRecompAndroid), for the command page fix brought into b4.
- [The412Banner](https://github.com/The412Banner/Banners-Turnip), for the driver builds, and the
  [Mesa](https://www.mesa3d.org) project, for the Turnip driver.
- [AMD FSR 1](https://github.com/GPUOpen-Effects/FidelityFX-FSR),
  [Snapdragon GSR](https://github.com/SnapdragonStudios/snapdragon-gsr), [SMAA](https://github.com/iryoku/smaa) and
  [libadrenotools](https://github.com/bylaws/libadrenotools). The other libraries and licenses are in
  [README-ORIGINAL.md](README-ORIGINAL.md).
- Changes made with [Claude Code](https://claude.com/claude-code) (Anthropic), directed and tested by one person.

*The Legend of Zelda* and *Breath of the Wild* are trademarks of Nintendo. This project isn't affiliated with or endorsed by
Nintendo. The code's license is in [LICENSE](LICENSE); third-party components keep their own licenses.
