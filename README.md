# crkbd-keymap

This repository contains my [crkbd](https://github.com/foostan/crkbd) keymap.

To try this keymap out on your board, set up qmk_firmware on your system as per the [guide](https://docs.qmk.fm/#/newbs_getting_started), then, while in the `qmk_firmware` directory, run the following commands:
```bash
git submodule add https://github.com/mtoohey31/crkbd-keymap ./keyboards/crkbd/keymaps/mtoohey31
qmk compile -kb crkbd/rev1 -km mtoohey31
```

You can safely ignore the `swapped-left-pins.patch` file, unless you also happen to have fried the same pins on your controller while building your board that I did 😅 , if you did somehow though (and also so that I don't forget) you can apply the patch file to qmk's crkbd `config.h` by running:
```bash
git apply keyboards/crkbd/keymaps/mtoohey31/swapped-left-pins.patch
```
...then commenting and recommenting lines 34 and 36 based on which keyboard half you're building the firmware for.
