keybrd Library Developer's Guide
================================
This guide if for maintaining and writing new classes for the keybrd library and its extension libraries.
The most common reason for adding new classes are:
* I/O expander classes
* custom layer schemes for multi-layer keyboards
* experimental features

Who this guide is for
---------------------
This guide is for the maintainers and developers of the keybrd library and it's extensions.
It is assumed the reader is familiar with the C++ language including pointers, objects, classes, static class variables, composition, aggregation, inheritance, polymorphism, and enum.
Row, Scanner, and Debouncer classes use bit manipulation.

Class inheritance diagrams
--------------------------

Keybrd library class inheritance diagram
```
    Row

	     ___ ScannerInterface ___
	    /          |             \
	Scanner_uC  Scanner_IOE  Scanner_ShiftRegsPISO


    PortIOE

	           PortWriteInterface
	              /        \
	PortWrite_PCA9655E  PortWrite_MCP23S17            (one PortWrite class for each IOE type)
 
              PortReadInterface
	             /        \
	PortRead_PCA9655E  PortRead_MCP23S17              (one PortRead class for each IOE type)
 
	    _ LED _
	   /       \
	LED_uC    LED_PCA9655E


	DebouncerInterface
	      |
	Debouncer_Samples

    ScanDelay

	LayerStateInterface
	     |
	LayerState


	Key
	 |____
	 |    \
	 |   Key_LayeredKeysBase
	 |      \____________________
	 |      /                    \
	 |   Key_LayeredKeys      Key_LayeredKeys1
	 |
	 |___________________________
	 |     \                     \
	 |   Key_LayeredScScBase  Key_LayeredCodeScBase
	 |      |                     |
	 |   Key_LayeredScSc      Key_LayeredCodeSc
	 |
	Code
	 |_____________________
	 |     \               \
	 |   Code_LayerLock  Code_LayerHold
	 |
	  \________________________________________________________
	       \           \            \           \              \
	     Code_Sc  Code_Shift  Code_AutoShift  Code_LEDLock  Code_Null
	                             /      \
	                        Code_ScS  Code_ScNS

```

Dependency diagrams
-------------------

Dependency diagram of example single-layer keyboard with LEDs
```
	        ____ Row ______
	       /      |        \
	Scanner_uC  Debouncer  Key ___
	      |                 |     \
	readPins               Code  Code_LEDLock
	                               |
	                             LED_PinNumber

```

Dependency diagram of example multi-layer keyboard with layer LEDs
```
	                                          LayerStates
	         ___________ Row ________________/__   |     \
	        /        /            \         /   \  |      \
	Scanner_uC  Debouncer  Key_LayeredKeys / Code_Layer  LED_PinNumber
	       |                           \  /
	  readPins                         Code

```

Dependency diagram of example shift registers Row
```
	                  _______ Row _______
	                 /         |         \
	RowScanner_ShiftRegsPISO  Debouncer  Key
	                                      |
	                                     Code

```

Dependency diagram of example I/O expander matrix with LEDs
```
	                 _________ Row ________
	                /             \        \
	        __ Scanner_IOE __   Debouncer  Key
	       /       |         \             /  \
	strobePin  PortWrite  PortRead      Code  Code_LEDLock
	             |   \      /   \              |
	             |    PortIOE  readPins       LED
	              \___________________________/ \
                                                pin

```

Class naming conventions
------------------------
Class names start with upper case letter.
Most derived-class names start with the base class name followed by "_" and a name e.g.
```
	Code
	  |
	Code_LayerLock

```
This convention leads to class names that convey information about the classes inheritance.
Underscore delineates base class name and sub-class name.  Capital letters delineate words.

Interface class names end with "Interface".
Except for Key, because sketches look nicer with short names defining Key[] arrays.

Layer-class naming conventions
------------------------------
Layer classes are explained in [tutorial_3a_multi-layer_keyboard.md](../tutorials/tutorial_3a_multi-layer_keyboard.md).

*Code_Layer* class names are concatenations of "Code_", "Layer" or layer name, and persistence.
Example persistences are:
* "Lock" - layer remains active after the layer key is released
* "Hold" - layer is active for as long as layer key is held down

Example Code_Layer class names:
* Code_LayerHold
* Code_LayerLock

*LayerState* class names start with "LayerState" and end with a descriptive name.
Example LayerState class names:
* LayerState    - basic LayerState class in keybrd library
* LayerState_DH - main LayerState for the keybrd_DH library
* LayerState_MF - LayerState for Mouse Function sub-layers in the keybrd_DH library

*Key_Layered* class names start with "Key_Layered" and end with a descriptive name.
Example Key_Layered class names:
* Key_LayeredScSc
* Key_LayeredKeys

Style guide
-----------
Following the style guide makes it easier for the next programmer to understand your code.
* For class names, see above section "Class naming conventions".
* Member names use camelCase starting with lowercase letter.
* Use constants rather than macros, except for header guards.
* Global const names and static const names use ALL_CAPS_WITH_UNDERSCORE.
* Macros use ALL_CAPS_WITH_UNDERSCORE and have _MACRO suffix e.g. SAMPLE_COUNT_MACRO
* Header guards have _H suffix e.g. #ifndef FILE_NAME_H
* Pointer names are prefixed with "ptr" e.g. ptrRow =  &row;
* Arrays names use the plural of the element name e.g. Row* const = ptrsRows { &row0,  &row1 };
* Pass arrays using array notation rather than pointer notation:
```
        void printArray(char[] array);
    not
        void printArray( char* array);
```
* In constructor's initialization list, use same names for fields and constructor parameters.
* Do not use new or malloc (make memory leaks impossible).
* Document class interface in .h file, above the class declaration.
* Code should be self-documenting.  A simple function with a good name needs no comment.
* Code is automatically formatted before being pushed to the keybrd repository.
  The [astyle_cpp](astyle_cpp) file specifies the format:
    * Allman style indentation
    * indent 4 spaces
    * replace tabs with spaces
    * maximum code width of 100 columns

  <!-- http://stackoverflow.com/questions/2198241/best-practice-for-c-function-commenting -->

Trace of keybrd scan
--------------------
Arduino does not have a debugger.
So here is a list of functions in the order that they are called.
The trace is of a one-row single-layer keybrd scan.

```
    loop()                                      for each row
        Row::process()
            Scanner_uC::scan()                      strobe row on
                                                        for each readPin
                                                            set readState bit
                                                    strobe row off
            Debouncer_Samples::debounce()           debounce
            Row::send()                         for each key in row
                                                    if falling edge
                Key_*::release()                        scanCode->release()
                    Code_*::release()                       Keyboard.release(scancode)
                                                    if rising edge
                Key_*::press()                          scanCode->press()
                    Code_*::press()                         Keyboard.press(scancode)
        scanDelay.delay();
         
```

The Arduino libraries
---------------------
The keybrd libraries compile on the Arduino IDE and make extensive use of the following [Arduino libraries](https://www.arduino.cc/en/Reference/Libraries):

    #include <Arduino.h>
    #include <Wire.h>
    #include <Keyboard.h>
    #include <Mouse.h>

<a rel="license" href="https://creativecommons.org/licenses/by/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://licensebuttons.net/l/by/4.0/88x31.png" /></a><br /><span xmlns:dct="http://purl.org/dc/terms/" property="dct:title">keybrd guide</span> by <a xmlns:cc="https://creativecommons.org/ns" href="https://github.com/wolfv6/keybrd" property="cc:attributionName" rel="cc:attributionURL">Wolfram Volpi</a> is licensed under a <a rel="license" href="https://creativecommons.org/licenses/by/4.0/">Creative Commons Attribution 4.0 International License</a>.<br />Permissions beyond the scope of this license may be available at <a xmlns:cc="https://creativecommons.org/ns" href="https://github.com/wolfv6/keybrd/issues/new" rel="cc:morePermissions">https://github.com/wolfv6/keybrd/issues/new</a>.
