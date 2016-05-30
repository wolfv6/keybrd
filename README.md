keybrd library for creating keyboard firmware
====================================================
keybrd library is an open source library for creating custom-keyboard firmware.
The resulting keyboard firmware is compatible with standard USB keyboard drivers.

keybrd library can support any keyboard configuration:
* one-piece
* split with I/O expander
* single-layer
* multiple-layer

Multiple-layer keyboards can write symbols without using the shift key:

    ~ ! @ # $ % ^ & * () _ {} | < > : ?

keybrd library leverages the Arduino environment to create keyboard firmware.
The Arduino development environment is free, and easy for novice programmers to setup and learn.

The keybrd library has been tested on the Teensy 2.0 microcontroller, MCP23018 I/O expander, and PCA9655E I/O expander.

> The public API should not be considered stable.
> Currently the keybrd library is limited to 8x8 matrices, which is enough for compact split keyboards.

Example minimal keybrd sketch
-----------------------------
<!-- todo after teensy LC bb, copy and remove annotations from keybrd_single-layer_2_annotated.ino -->
A [minimal keybrd sketch](tutorials/keybrd_2_single-layer_annotated/keybrd_2_single-layer_annotated.ino).
has about 50 lines of code and runs on a 4-key keyboard.
It runs on a breadboard and has rows, columns, and diodes just like the big keyboards.
The sketch is small because the keybrd library takes care of the low-level details.

The keybrd tutorial 1 shows how to make a breadboard keyboard.
The remaining [keybrd tutorials](tutorials) show how to create custom keybrd firmware.

Example complex keybrd sketch
-----------------------------
The keybrd_DH emulates the DataHand keyboard.
It has 72 keys, 4 layers, 6 sub-layers, 2 matrices, 8 LEDs, and blinking LEDs.
The keybrd_DH and its instantiation files contain about 800 lines of code.

[mainSketch.ino](https://github.com/wolfv6/keybrd_DH/blob/master/examples/keybrd_DH/mainSketch.cpp)<br>
[instantiations_ports.h](https://github.com/wolfv6/keybrd_DH/blob/master/src/instantiations_ports.h)<br>
[instantiations_LEDs.h](https://github.com/wolfv6/keybrd_DH/blob/master/src/instantiations_LEDs.h)<br>
[instantiations_codes.h](https://github.com/wolfv6/keybrd_DH/blob/master/src/instantiations_codes.h)<br>
[instantiations_matrix.h](https://github.com/wolfv6/keybrd_DH/blob/master/src/instantiations_matrix.h)

Support
-------
[Guides](doc) and [tutorials](tutorials) are provided.
Please ask a questions in [issues](https://github.com/wolfv6/Keybrd/issues) if something is not clear.
