keybrd Library User's Guide
===========================
keybrd is an open source library for creating custom-keyboard firmware.
The resulting keyboard firmware is compatible with standard USB keyboard drivers.

This guide shows how to
* set up the Arduino development environment
* install the keybrd library
* compile and load keybrd firmware

The Arduino development environment is free and simple as possible.
Its easy for novice programmers to setup and learn.

## Who this guide is for
This guide is for anyone who wants to use the keybrd library to develop keyboard firmware.

A reader with programming experience, but no C++ experience, would understand the tutorials well enough to modify existing keybrd sketches.
An experienced C++ programmer would be able to write original sketches and classes.

The library is written in the C++ language and uses pointers, objects, classes, static class variables, composition, inheritance, and enum.

## Microcontroller board requirements
The keybrd library works with Teensy and Arduino boards.

[Teensy LC](https://www.pjrc.com/teensy/teensyLC.html) has 8K RAM, which is more than enough memory for any keyboard.

keybrd has been tested on the DodoHand keyboard with Teensy 2.0 and PCA9655E I/O expander using the keybrd_DH sketch.

Teensy LC is preferred over the older Teensy 2.0 for it's larger memory capacity and lower price.

## Getting started with Teensy, Arduino IDE, and keybrd
The Arduino IDE is used to

1. edit sketches
2. compile sketches into HEX files
3. load the HEX file onto the microcontroller

Teensyduino is a software add-on for the Arduino IDE that allows it to compile to Teensy.

[Teensy Getting Started](http://www.pjrc.com/teensy/first_use.html) is a good way to familiarize yourself with Teensy.
[Arduino Development Environment](http://arduino.cc/en/guide/Environment) is a brief description.

The following install and setup steps create an Arduino development environment for keybrd sketches.

### Install Arduino IDE and Teensyduino
The following install steps are modified from the [Teensyduino download page](https://www.pjrc.com/teensy/td_download.html)

For Linux:

1. Download and extract the Arduino software to the /opt directory:

       /opt/arduino-1.x.x 

2. The "Linux udev rules" link is at top right of page.
   Save the teensy.rules file in /etc/udev/rules.d/

3. "Teensyduino Files" installer links are at top of page.
   Download the installer to your Downloads directory.
   Make the installer executable:

       $ chmod 755 teensyduino.64bit

   Run the teensyduino installer and fill the form fields:

       Arduino location to install Teensyduino: /opt/arduino-1.x.x 
       Libraries to Install: None

4. Launch Arduino IDE from /opt/arduino-1.x.x/arduino

### Download and unpack keybrd-master.zip into your Arduino directory
<!-- todo update after testing Arduino library manager
link from tutorial 7 ## Publishing
    https://www.arduino.cc/en/Guide/Libraries
     * Installing Additional Arduino Libraries
     * Using the Library Manager
 -->

Down load keybrd-master.zip from the [Download ZIP](https://github.com/wolfv6/keybrd) button.

Unpack keybrd-master.zip into your Arduino directory on your system (default location is ~/Documents/Arduino/).

### Install keybrd library and keybrd extension libraries
<!-- todo update after testing Arduino library manager -->

The keybrd library contains the foundation classes for creating a keyboard firmware.
For emphasis, it is sometimes referred to as the "core keybrd library".

keybrd extension libraries contain additional classes that extend the keyboard library.
keybrd extension library names are prefixed with "keybrd_".

The Arduino IDE looks for libraries in Arduino/libraries/.
For example, the DodoHand keyboard requires that the core keybrd library and the keybrd_DH extension library be installed:
* Arduino/libraries/keybrd/
* Arduino/libraries/keybrd_DH/

A keybrd extension library allows classes to be shared by multiple sketches without polluting the core keybrd library with classes that other keyboards can not use.

### Setup Arduino IDE for compiling keybrd firmware
From the Arduino IDE tool bar, select: 
* Tools > Board > Teensy LC (or whatever board you are using)
* Tools > USB Type > Keyboard + Mouse + Joystick

These are optional:
* File > Preferences > Compiler warnings: All
* File > Preferences > check: Use external editor

A Sketchbook is a folder that the Arduino IDE uses to store sketches and libraries.
The default location for [Arduino libraries](https://www.arduino.cc/en/Guide/Libraries) is in

    ~/Documents/Arduino/libraries/

### Compile and load keybrd sketch
If it isn't already plugged in, plug the USB cable into the computer and controller.

> CAUTION: It is possible to loose control of your keyboard when running a keybrd sketch.
> If the keybrd sketch has a mouse object, it is also possible to loose control of your mouse.
> USB keyboard protocol is capable of spewing characters and mouse commands at up to 500 per second.
> Take the following precautions before uploading an untested keybrd sketch to a controller:
> * Save all files and close dangerous applications.
> * Park the cursor in an editor opened to a test file.
>   That way you can immediately see if the controller starts spewing characters.
> * Be prepared to turn off the controller:
>   turn off Teensy Loader's green "Auto" button and push Teensy's reset button
>   if that fails, unplug Teensy USB

Compile and load workflow:
 1. Open a keybrd sketch in the Arduino IDE.
 2. Prepare for loosing control of keyboard and mouse.
 3. On the Arduino IDE, click the Upload button.
 4. The Teensy boot loader window opens;
    you might need to press and release the pushbutton on the Teensy circuit board.

## Example keybrd sketches
Example keybrd sketches are in the [examples](../examples/) directory.
Extension libraries have their example sketches similarly located.

The example sketch names use the following conventions.

   **keybrd_feature_version.ino**

where
* **keybrd** is the library name e.g. keybrd, keybrd_DH
* **feature** is a distinguishing feature of the keybrd sketch e.g. breadboard, LED, sound, Dvorak
* **version** is the sketch's version number

The first field are mandatory, the remaining fields are optional.

## Diode orientation
The physical martix rows and columns on a keyboard can be in any direction or shape.
[diode](https://en.wikipedia.org/wiki/Diode) orientation is specified in [Matrix.h](https://github.com/wolfv6/keybrd/blob/master/src/Matrix.h)

![Diode](https://github.com/wolfv6/keybrd/blob/master/tutorials/images/120px-Diode_pinout_en_fr.svg.png)

Diagram is of typical through-the-hole diode in same alignment as diode symbol.
Cross bar and band depict the cathode.

## Troubleshooting check list
The following is a listing of items to check when a new keybrd sketch or keyboard is having trouble.

Development-environment items to check:
* If the keyboard has an I/O expander, power cycle (replug the USB) after loading the HEX file.
* If compile error: 'KEY_A' was not declared in this scope

  From the Arduino IDE tool bar, select: Tools > USB Type > Keyboard + Mouse + Joystick

Sketch items to check:
* For each row, number of keys in Row should equal number of colPort pins.
In this example, row_0 has six colPort pins in ptrsColPorts, and six keys in ptrsKeys_0:
```
    ColPort_AVR colPortB(DDRB, PORTB, PINB, 1<<0 | 1<<1 | 1<<2 | 1<<3 );
    ColPort_AVR colPortD(DDRD, PORTD, PIND, 1<<2 | 1<<3 );

    ColPort* const ptrsColPorts[] = { &colPortB, &colPortD };
    const uint8_t COL_PORT_COUNT = sizeof(ptrsColPorts)/sizeof(*ptrsColPorts);

    const Key* const ptrsKeys_0[] = { &k_00, &k_01, &k_02, &k_03, &k_04, &k_05 };
    Row row_0(ptrsKeys_0, &rowPortF, 1<<0, ptrsColPorts, COL_PORT_COUNT);
```
* Some of the constructors take array-element-count arguments, make sure that the correct counts are passed to the constructors.  Or use sizeof() like this example:
```
    Row* const ptrsRows[] = { &row0, &row1, &row2, &row3 };
    const uint8_t ROW_COUNT = sizeof(ptrsRows)/sizeof(*ptrsRows);
    Matrix matrix(ptrsRows, ROW_COUNT, 1);
```
* For multi-layered keyboards, the number of codes in each Key_Layered should equal the number of layers.

Hardware items to check:
* Connections
* Diode orientation
* 5 volts across power and ground
* To validate keyboard hardware, modify the simple single-layer keybrd sketch from the tutorial.

<!-- todo after teensy LC bb, linke to minimal keybrd sketch
[minimal keybrd sketch](blob/master/tutorials/keybrd_2_single-layer_annotated/keybrd_2_single-layer_annotated.ino).
 -->

## Keybrd nomenclature
**[scancode](http://en.wikipedia.org/wiki/Scancode)** -
Is a 16-bit integer assigned to a key position on a keyboard.
The keyboard sends a scancode to the computer for every key press and release.

**[Layers](http://deskthority.net/wiki/Layer)** -
are key bindings provided by the keyboard firmware.
The standard [IBM PC keyboard](http://en.wikipedia.org/wiki/IBM_PC_keyboard) has one layer.
Many compact keyboards have an additional [Fn layer](http://en.wikipedia.org/wiki/Fn_key).
The [Neo layout](http://neo-layout.org/index_en.html) has 6 layers.

**Layer code** - is an integer assigned to a layer.

**Layer scheme** - is a system for changing layers while typing.
                   A single-layer scheme does not change layers.

**Layout** - is the placement of keys.  Key caps are often labeled to show a keyboard's layout.

**[Matrix](http://pcbheaven.com/wikipages/How_Key_Matrices_Works/)** - is a collection of switches connected by rows and columns.

**[Bounce](http://en.wikipedia.org/wiki/Switch#Contact_bounce)** -
Keyboard switches are made of moving contacts.
When the contacts close, they bounce apart one or more times before making steady contact.
A debouncer removes the bounce so that a key press is sent to the computer only once.

**[Modifier key](http://en.wikipedia.org/wiki/Modifier_key)** - is a special key on a computer keyboard that temporarily modifies the normal action of another key when pressed together e.g. Shift, Alt, or Ctrl.
By themselves, modifier keys usually do nothing; that is, pressing any of the Shift, Alt, or Ctrl keys alone does not trigger any action from the computer.

**Sketch** - is the name that Arduino uses for a program

**keybrd sketch** - is an Arduino sketch that uses the keybrd library to define a keyboard firmware.

<a rel="license" href="http://creativecommons.org/licenses/by/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by/4.0/88x31.png" /></a><br /><span xmlns:dct="http://purl.org/dc/terms/" property="dct:title">keybrd guide</span> by <a xmlns:cc="http://creativecommons.org/ns#" href="https://github.com/wolfv6/keybrd" property="cc:attributionName" rel="cc:attributionURL">Wolfram Volpi</a> is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by/4.0/">Creative Commons Attribution 4.0 International License</a>.<br />Permissions beyond the scope of this license may be available at <a xmlns:cc="http://creativecommons.org/ns#" href="https://github.com/wolfv6/keybrd/issues/new" rel="cc:morePermissions">https://github.com/wolfv6/keybrd/issues/new</a>.
