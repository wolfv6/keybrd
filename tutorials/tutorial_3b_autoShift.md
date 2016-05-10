Tutorial 3b - autoShift
=======================
When you finish this tutorial your keyboard will be able to automatically shifted characters.

## AutoShift
Some mulit-layer keyboards have a symbols layer that writes symbols without using the shift key:

    ~ ! @ # $ % ^ & * () _ {} | < > : ?

The keybrd library does this by automatically sending the MODIFIERKEY_SHIFT scancode.
The [keybrd_3_autoShift_annotated.ino](keybrd_proj/keybrd/examples/keybrd_3_autoShift_annotated/keybrd_3_autoShift_annotated.ino)
sketch explains the AutoShift feature.

Two keybrd classes use AutoShift:
* Code_ScS
* Code_ScNS

## Exercises
1) Modify the keybrd_3_autoShift_annotated sketch to make a 3-layer keyboard with two Code_LayerHold objects.

| Layout | **0** | **1** |
|:------:|-------|-------|
|  **0** | a ! 6 | b @ 7 |
|  **1** | sym   | num   |
