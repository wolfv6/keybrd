Tutorial 3f - autoShift
=======================
Some multi-layer keyboards have a symbols layer that writes symbols without using the shift key:

    ~ ! @ # $ % ^ & * () _ {} | < > : ?

The keybrd AutoShift class automatically sends a MODIFIERKEY_SHIFT scancode as needed.
Two keybrd classes use AutoShift:
* Code_ScS
* Code_ScNS

The [keybrd_3f_autoShift.ino](keybrd_3f_autoShift/keybrd_3f_autoShift.ino) sketch explains the AutoShift feature.
It will run on the basic breadboard keyboard described in [tutorial_1_breadboard_keyboard.md](tutorial_1_breadboard_keyboard.md).
After reading the sketch you too will be able to automatically shifted characters.

![basic breadboard keyboard](keybrd_1_breadboard/breadboard_keyboard_2x2.JPG "basic breadboard keyboard")

Exercises
---------
1) Modify the keybrd_3f_autoShift sketch to make a 3-layer keyboard with a default layer and two Code_LayerHold objects.

| Layout | **0** | **1** |
|:------:|:-----:|:-----:|
|  **0** | a ! 1 | b @ 2 |
|  **1** |  sym  |  num  |

2) Modify the keybrd_3f_autoShift sketch to write 1 and 2, regardless of if shift is held down or not (hint: use Code_ScNS).

| Layout | **0** | **1** |
|:------:|-------|-------|
|  **0** | a  1  | b  2  |
|  **1** |  fn   | shift |

<br>
<a rel="license" href="https://creativecommons.org/licenses/by/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://licensebuttons.net/l/by/4.0/88x31.png" /></a><br /><span xmlns:dct="http://purl.org/dc/terms/" property="dct:title">keybrd tutorial</span> by <a xmlns:cc="https://creativecommons.org/ns" href="https://github.com/wolfv6/keybrd" property="cc:attributionName" rel="cc:attributionURL">Wolfram Volpi</a> is licensed under a <a rel="license" href="https://creativecommons.org/licenses/by/4.0/">Creative Commons Attribution 4.0 International License</a>.<br />Permissions beyond the scope of this license may be available at <a xmlns:cc="https://creativecommons.org/ns" href="https://github.com/wolfv6/keybrd/issues/new" rel="cc:morePermissions">https://github.com/wolfv6/keybrd/issues/new</a>.
