keybrd Tutorial 4 - split keyboard with I/O Expander
====================================================
When you finish this tutorial you will be able to be able to modify a 2-matrix keybrd sketch to suite your own split keyboard design.

Overview of split keyboard with I/O Expander
--------------------------------------------
The breadboard in this picture models a split keyboard.
![breadboard keyboard with 2 rows and 4 columns of keys](images/breadboard_keyboard_2x5_labeled.jpg "2x5 breadboard keyboard")

The breadboard's four bus strips are used as rows.
Two rows (blue buses) are connected to the microcontroller.
Two rows (red buses) are connected to the I/O expander.

The I/O expander is a MCP23S17.
It has a small notch on one end, which identifies pin 1.
In the picture, pin 1 is on the left end.

The MCP23S17 communicates via SPI protocol, where Teensy LC is the master, and MCP23S17 is slave.
The Teensy LC and MCP23S17 are connected via 6 jumper wires:

|CONNECTION          |Teensy LC|MCP23S17|
|:------------------:|---------|--------|
|ground              | GND     | VSS    |
|power               | 3.3v    | VDD    |
|Serial Clock        | SCK0    | SCK    |
|Master Out, Slave In| MOSI0   | SI     |
|Master In, Slave Out| MISO0   | SO     |
|Chip Select         | CS0     | /CS    |

A decoupling capacitor suppresses high-frequency noise from the power supply.

MCP23S17's I/O expander address is configured by hardware pins.
The MCP23S17 with all address pins grounded has an device address of 0x20.

The MCP23S17's /RESET pin is connected to VDD.

The MCP23S17 I/O expander has two ports.  Each port has eight pins.
Port B is connected to the matrix's rows.
Port A is connected to the matrix's columns.

Building a split keyboard with I/O Expander
-------------------------------------------
Starting with the basic breadboard keyboard described in [tutorial_1_breadboard_keyboard.md](tutorial_1_breadboard_keyboard.md), add parts as described above.
Refer to the MCP23S17 datasheet to locate its pins.

<!-- todo schematic with IOE power decoupling capacitor
This schematic was written by consulting the I/O expander's datasheet and using the ?? tool. -->

Sketch for split keyboard with I/O Expander
-------------------------------------------
The [keybrd_4c_split_with_IOE.ino](keybrd_4c_split_with_IOE/keybrd_4c_split_with_IOE.ino)
 sketch explains how the I/O Expander works on a keyboard.

<a rel="license" href="https://creativecommons.org/licenses/by/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://licensebuttons.net/l/by/4.0/88x31.png" /></a><br /><span xmlns:dct="http://purl.org/dc/terms/" property="dct:title">keybrd tutorial</span> by <a xmlns:cc="https://creativecommons.org/ns" href="https://github.com/wolfv6/keybrd" property="cc:attributionName" rel="cc:attributionURL">Wolfram Volpi</a> is licensed under a <a rel="license" href="https://creativecommons.org/licenses/by/4.0/">Creative Commons Attribution 4.0 International License</a>.<br />Permissions beyond the scope of this license may be available at <a xmlns:cc="https://creativecommons.org/ns" href="https://github.com/wolfv6/keybrd/issues/new" rel="cc:morePermissions">https://github.com/wolfv6/keybrd/issues/new</a>.
