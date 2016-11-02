keybrd Library User's Guide
===========================
keybrd is a library for creating custom-keyboard firmware.
This guide shows how to:
* set up the Arduino development environment
* install the keybrd library
* compile and load keybrd firmware

The Arduino development environment is free and simple as possible.
Its easy for novice programmers to setup and learn.

Who this guide is for
---------------------
This guide is for anyone who wants to use the keybrd library to develop keyboard firmware.

A reader with programming experience, but no C++ experience, would understand the tutorials well enough to modify existing keybrd sketches.
An experienced C++ programmer would be able to write original sketches and classes.

The library is written in the C++ language.
keybrd sketches use keybrd classes, objects pointers, aggregation, and static class variables.

Microcontroller board requirements
----------------------------------
The keybrd library works with Teensy and Arduino compatible boards with at least 2 KB SRAM.

[Teensy LC](https://www.pjrc.com/teensy/teensyLC.html) is the preferred board for the keybrd library and is used in the tutorials.  Teensy LC has 8 KB SRAM, which is enough memory for any keyboard.

Getting started with Teensy, Arduino IDE, and keybrd
----------------------------------------------------
The Arduino IDE is used to

1. edit sketches
2. compile sketches into HEX files
3. load the HEX file onto the microcontroller

Teensyduino is a software add-on for the Arduino IDE that allows it to compile to Teensy.

[Teensy Getting Started](http://www.pjrc.com/teensy/first_use.html) is a good way to familiarize yourself with Teensy.
[Arduino Development Environment](http://arduino.cc/en/guide/Environment) is a brief description.

The following steps create an Arduino development environment for keybrd sketches.

### Install Arduino IDE and Teensyduino
The following install steps are modified from the [Teensyduino download page](https://www.pjrc.com/teensy/td_download.html).

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
       Libraries to Install: keybrd

4. Launch Arduino IDE from /opt/arduino-1.x.x/arduino

### Install keybrd extension libraries
The keybrd library contains the foundation classes for creating a keyboard firmware.
For emphasis, it is sometimes referred to as the "core keybrd library".

keybrd extension libraries contain additional classes that extend the keyboard library.
keybrd extension library names are prefixed with "keybrd_".

Instructions for installing Arduino libraries are at: http://www.arduino.cc/en/Guide/Libraries

The default location for Arduino libraries is ~/Documents/Arduino/libraries/.

For example, the DodoHand keyboard requires the core keybrd library and the keybrd_DH extension library be installed.
After installing the libraries, my Arduino directory looks like this:
* ~/Documents/Arduino/libraries/keybrd/
* ~/Documents/Arduino/libraries/keybrd_DH/

### Setup Arduino IDE for compiling keybrd firmware
From the Arduino IDE tool bar, select: 
* Tools > Board > Teensy LC (or whatever board you are using)
* Tools > USB Type > Keyboard + Mouse + Joystick

These are optional:
* File > Preferences > Compiler warnings: All
* File > Preferences > check: Use external editor

### Compile and load keybrd sketch
If it isn't already plugged in, plug the USB cable into the computer and controller.

> CAUTION: It is possible to loose control of your keyboard when running a keybrd sketch.
> If the keybrd sketch has a mouse object, it is possible to loose control of your mouse too.
> USB keyboard protocol is capable of spewing characters and mouse commands at up to 500 per second.
> Take the following precautions before uploading an untested keybrd sketch to a controller:
> * Save all files and close dangerous applications.
> * Park the cursor in an editor opened to a test file.
>   That way you can immediately see if the controller starts spewing characters.
> * Be prepared to turn off the controller:
>   turn off Teensy Loader's green "Auto" button and push Teensy's reset button or unplug Teensy USB.

Compile and load workflow:
 1. Open a keybrd sketch in the Arduino IDE.
 2. Prepare for loosing control of keyboard and mouse.
 3. On the Arduino IDE, click the Upload button.
 4. The Teensy boot loader window opens
    (you might need to press and release the pushbutton on the Teensy circuit board).

Example keybrd sketches
-----------------------
Example keybrd sketches are in the examples and tutorials directories.
Extension libraries have their example sketches similarly located.

Active state and diode orientation
----------------------------------
Active state is set in the sketch by the scanner.
The following instructions are for setting active state for a Scanner_uC class
(Scanner_ShiftRegs74HC165 and Scanner_Port classes is similar).

For active low:
* Orient diodes with cathode (banded end) towards the write pins (row)
* Instantiate the scanner in the sketch with strobeOn LOW, like this:
```
Scanner_uC scanner(LOW, readPins, readPinCount);
```

For active high:
* Add an external 10k pull-down resistor to each read pin.
* Orient diodes with cathode (banded end) towards the read pins.
* Instantiate the scanner in the sketch with strobeOn HIGH, like this:
```
Scanner_uC scanner(HIGH, readPins, readPinCount);
```

Troubleshooting check list
--------------------------
The following is a listing of items to check when a new keybrd sketch or keyboard hardware is having trouble.

Development-environment items to check:
* If the keyboard has an I/O expander, power cycle (replug the USB) after loading the HEX file.
* Sometimes sketch will not loading properly if two instances of Arduino IDE are open.
* For compile error:
```
    'KEY_A' was not declared in this scope
```
  Where 'KEY_A' could be any scan code.
  Fix this error from the Arduino IDE tool bar: Tools > USB Type > Keyboard + Mouse + Joystick

* If last line in Arduino IDE says "Low memory available",
  second-to-last line should say "leaving 100 bytes for local variables" or more bytes.
* In keybrd/src/config_keybrd.h file, read_pins_t defaults to uint32_t.
  If more memory is needed, 8-bit controllers can use uint8_t.

Sketch items to check:
* For each row, number of read pins in Row should equal number of keys.
In this example, row_0 has 2 read pins and 2 keys:
```
    uint8_t readPins[] = {14, 15};
    uint8_t READ_PIN_COUNT = sizeof(readPins)/sizeof(*readPins);

    Key* ptrsKeys_0[] = { &s_a, &s_b };
    Row_uC row_0(0, readPins, READ_PIN_COUNT, ptrsKeys_0);
```
* The scanner should have enough readPins to cover all the keys of the longest row.
  (rows with fewer keys will have unused read pins)
* read_pins_t size in keybrd/src/config_keybrd.h file should cover all the read pins.
* Some of the constructors take array-element-count arguments, make sure that the correct counts are passed to the constructors.  Or use sizeof() like the preceding example.
* For multi-layered keyboards, the number of codes in each Key_Layered should equal the number of layers.

Hardware items to check:
* Continuity of connections
* 3.3 or 5 volts across power and ground
* Diode orientation
* To validate keyboard hardware, modify the simple [keybrd_1_breadboard.ino](../tutorials/keybrd_1_breadboard/keybrd_1_breadboard.ino) sketch.

Debugging:
Arduino doesn't have a debugger.  You can print values like this:
    Keyboard.print(" var="); Keyboard.print(var);
    Keyboard.print(" bitPattern="); Keyboard.println(bitPattern, BIN);
    delay(200);
The delay is so prints in a loop don't print too fast.

Keybrd nomenclature
-------------------
**[scancode](http://en.wikipedia.org/wiki/Scancode)** -
Is a 16-bit integer assigned to a key position on a keyboard.
The keyboard sends a scancode to the computer for every key press and release.

**[layers](http://deskthority.net/wiki/Layer)** - are key bindings provided by the keyboard firmware.  For example,
* The classic [IBM PC keyboard](http://en.wikipedia.org/wiki/IBM_PC_keyboard) has one layer.
* Many compact keyboards have an additional [Fn layer](http://en.wikipedia.org/wiki/Fn_key).
* The [Neo layout](http://neo-layout.org/index_en.html) has 6 layers.

**Layer id** - is an integer assigned to a layer.

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

<a rel="license" href="https://creativecommons.org/licenses/by/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://licensebuttons.net/l/by/4.0/88x31.png" /></a><br /><span xmlns:dct="http://purl.org/dc/terms/" property="dct:title">keybrd guide</span> by <a xmlns:cc="https://creativecommons.org/ns" href="https://github.com/wolfv6/keybrd" property="cc:attributionName" rel="cc:attributionURL">Wolfram Volpi</a> is licensed under a <a rel="license" href="https://creativecommons.org/licenses/by/4.0/">Creative Commons Attribution 4.0 International License</a>.<br />Permissions beyond the scope of this license may be available at <a xmlns:cc="https://creativecommons.org/ns" href="https://github.com/wolfv6/keybrd/issues/new" rel="cc:morePermissions">https://github.com/wolfv6/keybrd/issues/new</a>.
