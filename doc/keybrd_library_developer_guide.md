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

Custom Row classes
------------------
Row classes are central to the keybrd library.
Row is an abstract base class that allows flexibility in designing derived Row classes:
* Row functions can be overridden in a derived class
* choice of Debouncers
* choice of Scanners

This example illustrates the custom Row classes for a fictional keybrd_Ext extension library.
The keybrd_Ext library is for a split keyboard with a matrix on each hand and sticky keys.

Row_Ext::keyWasPressed() overrides Row::keyWasPressed() which is used to unstick sticky keys.

Row_Ext_uC and Row_Ext_ShiftRegisters are a custom classes composed of stock keybrd library classes.<br>
Row_Ext_uC uses Scanner_uC to scan the primary matrix.<br>
Row_Ext_ShiftRegisters uses Scanner_ShiftRegs74HC165 to scan the peripheral matrix.

Class inheritance diagram
```

    	    Row
	         |
	       Row_Ext                                (override Row::keyWasPressed() )
          /      \
    Row_Ext_uC  Row_Ext_ShiftRegisters            (inherit Row_Ext::keyWasPressed() )


	Scanner_uC  Scanner_ShiftRegs74HC165

```

Dependency diagram
```

	         ________ Row_Ext_uC[1] ______________
	        /            |                        \
	Scanner_uC[1]  Debouncer_Samples[1]           Key[1..*]
	     /                                         |
	strobePin[1]                                  Code[1..*]


            _________ Row_Ext_ShiftRegisters[1] ________
	       /                            \               \
    Scanner_ShiftRegs74HC165[1]  Debouncer_Samples[1]  Key[1..*]
	      |                                             |
    strobePin[1]                                       Code[1..*]

```

Class inheritance diagrams
--------------------------

Keybrd library class inheritance diagram
```
	     ________ Row ___________
	    /          |             \
	Row_uC  Row_ShiftRegisters  Row_IOE (todo to be added)


	Scanner_uC  Scanner_Port  Scanner_ShiftRegs74HC165


	    PortIOE

	    PortWrite
	       |
	PortWrite_PCA9655E                          (one PortWrite class for each IOE type)
 
        PortRead
	       |
	PortRead_PCA9655E                           (one PortRead class for each IOE type)
 
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


	Key __
	 |    \
	 |   Key_LayeredKeysArray
	 |
	Code
	 |_____________________
	 |     \               \
	 |   Code_LayerLock  Code_LayerHold
	 |
	 |___________________________
	 |     \                     \
	 |   Code_LayeredScScBase  Code_LayeredCodeScBase
	 |      |                     |
	 |   Code_LayeredScSc      Code_LayeredCodeSc
	 |
	 |_________________________________________________________
	       \           \            \           \              \
	     Code_Sc  Code_Shift  Code_AutoShift  Code_LEDLock  Code_Null
	                             /      \
	                        Code_ScS  Code_ScNS

```

Dependency diagrams
-------------------

Dependency diagram of example single-layer keyboard with LEDs
```
	        _ Row_uC[1..*] _
	       /      |         \
	Scanner_uC  Debouncer  Keys[1..*] __
	                         |          \
	                       Code[1..*]  Code_LEDLock[1..*]
	                                     |
	                                   LED_PinNumber[1]

```

Dependency diagram of example multi-layer keyboard with layer LEDs
```
	                                          LayerStates[1..*]
	         ________ Row_uC[1..*] ___________/__    |         \
	        /           |         \          /   \   |          \
	Scanner_uC[1]  Debouncer[1]  Keys[1..*] / Code_Layer[1..*]  LED_PinNumber[0..*]
	                               |       /
	                             Code[1..*]

```

Dependency diagram of example peripheral matrix with shift registers
```
	              Row_ShiftRegisters[1..*]
	             /              \         \
	RowScanner_ShiftRegisters  Debouncer  Keys[1..*]
	                                       |
	                                      Code[1..*]

```

Dependency diagram of example peripheral matrix with I/O Expander and LEDs
```
	                 _____ Row_IOE[1..*] _________
	                /               \             \
	        __ Scanner_Port[1] __   Debouncer[1]  Keys[1..*] __
	       /          |          \                  |          \
	PortWrite[1]  strobePin[1]  PortRead[1]      Code[1..*]  Code_LEDLock[1..*]
	       \                   /   \                            |
	        \                 /   ColPins[1..*]              LED[1]
	         \               /
	           PortIOE[0..*]

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

*Code_Layered* class names start with "Code_Layered" and end with a descriptive name.
Example Code_Layered class names:
* Code_LayeredScSc
* Key_LayeredKeysArray

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
Refer to it like a table of contents while reading the keybrd library.

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
