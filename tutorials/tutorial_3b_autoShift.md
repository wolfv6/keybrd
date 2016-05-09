Tutorial 3b - autoShift
=======================
After reading this tutorial your keyboard will be able to be able to automatically shifted characters.

## AutoShift
Some mulit-layer keyboards have a symbols layer that writes symbols and numbers without using the shift key:

    ~ ! @ # $ % ^ & * () _ {} | < > ? 1 2 3 4 5 6 7 8 9 0

The keybrd library does this by automatically sending the MODIFIERKEY_SHIFT scancode.
This annotated sketch demonstrates the AutoShift feature: [keybrd_3_autoShift_annotated.ino](keybrd_proj/keybrd/examples/keybrd_3_autoShift_annotated/keybrd_3_autoShift_annotated.ino)

Two keybrd classes use AutoShift:
* Code_ScS
* Code_ScNS

## Exercises
1) Modify the keybrd_3_autoShift_annotated sketch to make a 3-layer keyboard with two Code_LayerHold objects.

| Layout | **0** | **1** |
|:------:|-------|-------|
|  **0** | a ! 6 | b @ 7 |
|  **1** | sym   | num   |
