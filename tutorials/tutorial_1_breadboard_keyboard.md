Tutorial 0 - breadboard keyboard
================================
When you finish this tutorial you will have a working keyboard and understand how its key matrix works.

[breadboard keyboard with 2 rows and 2 columns]
(images/breadboard_keyboard_2x2_labeled.jpg "2x2 breadboard keyboard")

## Why a breadboard keyboard is useful
A breadboard is the easiest way to learn keyboard electronics.
Electronics are fickle, you won't get everything right the first time, there is a learning curve.
Breadboards make the learning electronics faster and fun.

Breadboard keyboards have row-column matrices and diodes just like the big keyboards.
Compared to full size keyboards on PCBs, breadboard keyboards are easier to work with because:
* Parts can be reused in many different configurations
* A small keyboard is easier to trouble shoot
* Mistakes are easily corrected because no desoldering

Breadboard keyboards are useful for:
* learning keyboard electronics - diodes, micro controllers, I/O expanders
* learning the firmware development process
* prototyping circuits before making a PCB
* testing firmware concepts before building the keyboard hardware

## How a breadboard works
To understand the breadboard keyboard you will need to know the internal parts of a breadboard:
* terminal strip
* power rail

These are explained in [How to Use a Breadboard](https://learn.sparkfun.com/tutorials/how-to-use-a-breadboard)

## Breadboard keyboard starter kit
The parts needed to build all the Breadboard Keyboards in the keybrd tutorials are listed in [breadboard_keyboard_supplies.ods](breadboard_keyboard_supplies.ods).

Wire cutters (or nail clippers) is the only required tool.
A multi-meter is useful for trouble shooting.

## Building a basic breadboard keyboard
The basic breadboard has 4 switches and a microcontroller.

[breadboard keyboard with 2 rows and 2 columns of keys]
(images/breadboard_keyboard_2x2_labeled.jpg "2x2 breadboard keyboard")

The key matrix has two rows and two columns.
Breadboard power rails are repurposed as matrix rows.
Short bare wires connect switches into matrix columns.
Diodes connect switches to rows.

The green rectangle on the right is the Teensy 2.0 microcontroller.
The matrix rows and columns connect to the microcontroller via jumper wires.

Breadboard keyboard assembly instructions:

1. Cut leads to length.
 * tactile-switch-lead length 6 to 8 mm
 * diodes 22 to 24 mm total end-to-end length, and save the cut offs, they will be used in steps 2 and 3
2. Insert parts into the breadboard as shown in the picture.
 * orient the switches such that the leads are on separate terminal strips
 * orient diodes with cathode (banded end) towards the row (power strip)
 * use the diode cut offs to connect switches into columns
3. Insert jumper wires connecting Teensy2 to the matrix rows and columns.
 * follow pin connections table (below) and consult pinout diagram in
   [Connecting Teensy 2.0 to a Keyboard](connecting_teensy2_to_keyboard.md)

**Teensy 2.0 pin connections table**

| Pin number | Row  Column |
|------------|-------------|
| 21         | row_0       | todo this table might not match the sketches
| 20         | row_1       |
| 0          | col_0       |
| 1          | col_1       |

## Compiling and loading the keyboard firmware
Follow the [keybrd Library User's Guide](todo /doc/keybrd_library_user_guide.md) to set up the Arduino environment and to compile and load keybrd firmware onto the keyboard's controller.

## How a keyboard matrix works
Now that you have built your first breadboard keyboard, you can dig in and learn how it actually works.
This excellent article explains how the microcontroller, matrix, switches and diodes work together:
[How a Key Matrix Work](http://pcbheaven.com/wikipages/How_Key_Matrices_Works/)

## Bigger breadboard keyboards
Sometimes its useful to prototype the full keyboard matrix before designing the PCB.
Several breadboards can be tied together into one.

[big breadboard keyboard](breadboard_big.jpg "breadboard_big.jpg")
