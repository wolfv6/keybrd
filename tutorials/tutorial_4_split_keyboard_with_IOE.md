keybrd Tutorial 4 - split keyboard with I/O Expander
====================================================
When you finish this tutorial you will be able to be able to modify a 2-matrix keybrd sketch to suite your own split keyboard design.

## Overview of split keyboard with I/O Expander
The breadboard in this picture models a split keyboard.
![breadboard keyboard with 2 rows and 4 columns of keys](images/breadboard_keyboard_2x5_labeled.jpg "2x5 breadboard keyboard")

There is a total of 4 matrix rows, each on a breadboard power rail.

The right matrix is connected to a microcontroller.
The left matrix is connected to a I/O expander.

The I/O expander has a small notch on one end, which identifies the end with pin 1.
In the picture, pin 1 is on the right end.

The microcontroller and I/O expander are connected by 4 jumper wires:
* ground
* power
* Serial CLock signal (SCL)
* Serial DAta signal (SDA)

A capacitor on the power pin smooths power to the I/O expander.

The microcontroller and I/O expander communicate via [I2C](http://en.wikipedia.org/wiki/I%C2%B2C) bus, which consists of two signals: SCL and SDA.
Two resistors pull-up voltage on the SCL and SDA.

I/O expander I2C address is configured by three hardware pins (AD0, AD1, AD2).

The I/O expander has two ports.  Each port has eight pins.
One port is connected to the matrix's rows.  The other port is connected to the matrix's columns.

## Building a split keyboard with I/O Expander
The split keyboard is built on the basic breadboard keyboard described in [tutorial_1_breadboard_keyboard.md](tutorial_1_breadboard_keyboard.md)

<!-- todo add schematic with a capacitor to IOE power
This schematic was written by consulting the I/O expander's datasheet and using the ?? tool. -->

Continuing from the basic breadboard keyboard instructions:

4. Insert the I/O expander

5. Install I/O expander power
* ground
* power
* capacitor

6. Install I2C bus
* SCL
* SDA
* pull-up resistors on SCL and SDA

7. configure I2C address

8. Assemble key matrix as shown in the picture.

9. Connect I/O expander ports to matrix rows and columns

## Sketch for split keyboard with I/O Expander
The [keybrd_4_split_with_IOE_annotated.ino](keybrd_4_split_with_IOE_annotated/keybrd_4_split_with_IOE_annotated.ino)
 sketch explains how the I/O Expander works on a keyboard.

<a rel="license" href="http://creativecommons.org/licenses/by/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by/4.0/88x31.png" /></a><br /><span xmlns:dct="http://purl.org/dc/terms/" property="dct:title">keybrd tutorial</span> by <a xmlns:cc="http://creativecommons.org/ns#" href="https://github.com/wolfv6/keybrd" property="cc:attributionName" rel="cc:attributionURL">Wolfram Volpi</a> is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by/4.0/">Creative Commons Attribution 4.0 International License</a>.<br />Permissions beyond the scope of this license may be available at <a xmlns:cc="http://creativecommons.org/ns#" href="https://github.com/wolfv6/keybrd/issues/new" rel="cc:morePermissions">https://github.com/wolfv6/keybrd/issues/new</a>.
