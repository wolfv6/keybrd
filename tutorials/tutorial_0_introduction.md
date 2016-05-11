Tutorial 0 - Introduction
=========================
The first two tutorials are intended to be read in sequence:
 1. Breadboard keyboard
 2. Single-layer keybrd

Tutorial 1 is about making a breadboard keyboard, which is used in tutorials 2 through 6.
Tutorial 2 is needed to understand the remaining tutorials.
The remaining tutorials can be read in any order.

You will need a breadboard keyboard with a Teensy 2.0 controller to run tutorial sketches 2 through 6.
If you use a different controller, you may have to change pin assignments and port classes.
If you already have a keyboard with an Arduino compatible controller, you can use that instead of a breadboard keyboard.
All the tutorial sketches use 2 to 8 keys.
If your keyboard has more keys, they are simply ignored by the sketch.

The tutorials assume the reader:
* is familiar with C++
* is new to Arduino, firmware, controllers, and the internal workings of keyboards

<!-- todo -->
> All the tutorial sketches are tested on teensy 2.0 and PCA9655E-D I/O expander

> The tutorial sketches will be changed to Teensy LC and MCP23018 I/O expander

> Some of the pictures do not match the sketches, they will be updated after changing to Teensy LC

> Schematic diagrams are missing from tutorials 2 and 4, they will be added after changing to Teensy LC

<a rel="license" href="http://creativecommons.org/licenses/by/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by/4.0/88x31.png" /></a><br /><span xmlns:dct="http://purl.org/dc/terms/" property="dct:title">keybrd tutorial</span> by <a xmlns:cc="http://creativecommons.org/ns#" href="https://github.com/wolfv6/keybrd" property="cc:attributionName" rel="cc:attributionURL">Wolfram Volpi</a> is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by/4.0/">Creative Commons Attribution 4.0 International License</a>.<br />Permissions beyond the scope of this license may be available at <a xmlns:cc="http://creativecommons.org/ns#" href="https://github.com/wolfv6/keybrd/issues/new" rel="cc:morePermissions">https://github.com/wolfv6/keybrd/issues/new</a>.
