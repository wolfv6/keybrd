Tutorial 3b - autoShift
=======================
Some mulit-layer keyboards have a symbols layer that writes symbols without using the shift key:

    ~ ! @ # $ % ^ & * () _ {} | < > : ?

The keybrd library does this by automatically sending a MODIFIERKEY_SHIFT scancode.

The [keybrd_3_autoShift_annotated.ino](keybrd_3_autoShift_annotated/keybrd_3_autoShift_annotated.ino) sketch explains the AutoShift feature.
After reading the sketch you too will be able to automatically shifted characters.

Two keybrd classes use AutoShift:
* Code_ScS
* Code_ScNS

## Exercises
1) Modify the keybrd_3_autoShift_annotated sketch to make a 3-layer keyboard with two Code_LayerHold objects.

| Layout | **0** | **1** |
|:------:|-------|-------|
|  **0** | a ! 6 | b @ 7 |
|  **1** | sym   | num   |

<a rel="license" href="http://creativecommons.org/licenses/by/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by/4.0/88x31.png" /></a><br /><span xmlns:dct="http://purl.org/dc/terms/" property="dct:title">keybrd tutorial</span> by <a xmlns:cc="http://creativecommons.org/ns#" href="https://github.com/wolfv6/keybrd" property="cc:attributionName" rel="cc:attributionURL">Wolfram Volpi</a> is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by/4.0/">Creative Commons Attribution 4.0 International License</a>.<br />Permissions beyond the scope of this license may be available at <a xmlns:cc="http://creativecommons.org/ns#" href="https://github.com/wolfv6/keybrd/issues/new" rel="cc:morePermissions">https://github.com/wolfv6/keybrd/issues/new</a>.
