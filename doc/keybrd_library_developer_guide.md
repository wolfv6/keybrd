keybrd Library Developer's Guide
================================
This guide if for maintaining and writing new classes for the keybrd library and its extension libraries.
The most common reason for new classes are:
* Port classes for micro controller or I/O expanders
* custom layer schemes for multi-layer keyboards
* experimental features

## Who this guide is for
This guide is for the maintainers and developers of the keybrd library and it's extensions.
It is assumed the reader is familiar with C++ language including pointers, objects, classes, static class variables, composition, aggregation, inheritance, polymorphism, and enum.
Debouncer and I/O expander use bit manipulation.

## Custom Row classes
The keybrd library is flexible for designing custom Rows
 * RowBase functions can be overridden in a derived class
 * choice of Debouncers
 * choice of Scanners

this example illustrates the custom Row classes for a fictional keybrd_Ext extension library
the keybrd_Ext library is for a split keyboard with a matrix on each hand
other custom Row classes would have a similar structure

Row_Ext::keyWasPressed() overrides RowBase::keyWasPressed()
Row_Ext::keyWasPressed() is used to unstick sticky keys

Row_Ext_uC scans the primary matrix
Row_Ext_ShiftRegisters scans the secondary matrix
Row_Ext_uC and Row_Ext_ShiftRegisters are a custom classes composed of stock keybrd library classes

Class inheritance diagram
```

    	   RowBase
	         |
	       Row_Ext                                (override RowBase::keyWasPressed() )
          /      \
    Row_Ext_uC  Row_Ext_ShiftRegisters            (inherit Row_Ext::keyWasPressed() )


	            RowScannerInterface
	              /           \
	RowScanner_PinsArray  RowScanner_SPIShiftRegisters

```

Dependency diagram
```

	         ________ Row_Ext_uC[1] _______________
	        /                     \                \
	RowScanner_PinsArray[1]  Debouncer_Samples[1]  Key[1..*]
	     /          \                               |
	strobePin[1]  readPins[1..*]                   Code[1..*]


                _____ Row_Ext_ShiftRegisters[1] ___________
	           /                        \                  \
    RowScanner_SPIShiftRegisters[1]  Debouncer_Samples[1]  Key[1..*]
	       /       \                                        |
    strobePin[1]  ROW_END[1]                               Code[1..*]

```

## Class inheritance diagrams

Keybrd library class inheritance diagram
```
	     _______ RowBase ________
	    /          |             \
	Row_uC  Row_ShiftRegisters  Row_IOE

	               _____ RowScannerInterface ______
	              /            |                   \
	RowScanner_PinsArray  RowScanner_PinsBitwise  RowScanner_SPIShiftRegisters


	IOExpanderPort

	    RowPort
	       |
	RowPort_PCA9655E                            (one RowPort class for each IOE type)
 
        ColPort
	       |
	ColPort_PCA9655E                            (one ColPort class for each IOE type)
 
	       ____ LED ____
	      /             \
	LED_PinNumber  LED_PCA9655E


	DebouncerInterface
	      |
	Debouncer_4Samples


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
	 |__________________________________________
	       \           \            \           \
	     Code_Sc  Code_Shift  Code_AutoShift  Code_LEDLock
	                         /      |      \
	                  Code_ScS  Code_ScNS  Code_ScNS_00

```

## Dependency diagrams

Example single-layer dependency diagram with LEDs
```
	         ___ Row_uC[1..*] ________
	        /               \         \
	RowScanner_PinsArray  Debouncer  Keys[1..*] __
	                                   |          \
	                                 Code[1..*]  Code_LEDLock[1..*]
	                                               |
	                                             LED_PinNumber[1]

```

Example multi-layer dependency diagram with layer LEDs
```
	                                                    LayerStates[1..*]
	         ________ Row_uC[1..*] _____________________/__    |         \
	        /                     \         \          /   \   |          \
	RowScanner_PinsArray[1]  Debouncer[1]  Keys[1..*] / Code_Layer[1..*]  LED_PinNumber[0..*]
	                                         |       /
	                                       Code[1..*]

```

Example secondary matrix with shift registers dependency diagram
```
	            Row_ShiftRegisters[1..*]
	             /              \         \
	RowScanner_ShiftRegisters  Debouncer  Keys[1..*]
	                                       |
	                                      Code[1..*]

```

Example secondary matrix with I/O Expander dependency diagram with LEDs
```
	                 ___ Row_IOE[1..*] _________
	                /             \             \
	  RowScanner_PinsBitwise[1]  Debouncer[1]  Keys[1..*] __
	     /         |        \                    |          \
	RowPort[1]  RowPin[1]  ColPort[1]          Code[1..*]  Code_LEDLock[1..*]
	     \                /   \                              |
	      \              /   ColPins[1..*]                 LED[1]
	       \            /
	      IOExpanderPort[0..*]

```

## Class naming conventions
Class names start with upper case letter.
Most derived-class names start with the base class name followed by "_" and a name e.g.
```
	Code
	  |
	Code_LayerLock

```
This convention leads to class names that convey information about the classes inheritance.
Underscore delineates base class name and sub-class name.  Capital letters delineate words.

## Layer-class naming conventions
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

## Style guide
Following the style guide makes it easier for the next programmer to understand your code.
* For class names, see above section "Class naming conventions"
* For member names, use camelCase starting with lowercase letter.
* Use constants rather than macros, except for header guards.
* For constant names that could be macros, use ALL_CAPS_AND_UNDERSCORE.
    * **ITEM_COUNT** is a constant number of items.
    * **itemCount** is a variable number of items.
* Use header guards CLASS_NAME_H.
* Prefix pointer name with "ptr" e.g. ptrRow =  &row;
* Name arrays using the plural of element name e.g. Row* const = ptrsRows { &row0,  &row1 };
* Pass arrays using array notation rather than pointer notation.  Use
```
        void printArray(char[] array);
    not
        void printArray( char* array);
```
* In constructor's initialization list, use same names for fields and constructor parameters.
* Do not use new or malloc (making memory leaks impossible).
* Document class interface in .h file, above the class declaration.
* Code should be self-documenting.  The only comments should be things that may need clarification.  A simple function with a good name needs no comment.
* Code is automatically formated before being pushed to the keybrd repository.
  The [astyle_cpp](astyle_cpp) file specifies the format:
    * Allman style indentation
    * indent 4 spaces
    * replace tabs with spaces
    * maximum code width of 100 columns

  <!-- http://stackoverflow.com/questions/2198241/best-practice-for-c-function-commenting -->

## Trace of keybrd scan
Arduino does not have a debugger.
So here is the next best thing; a list of functions in the order that they are called.
The trace is of a single-layer keybrd scan (no LEDs and no I/O expander).
Refer to it like a table of contents while reading the keybrd library.

```
    loop()                                      for each row
        RowBase::process()
            RowBase::wait()                         delay time for debounce
            RowScanner_PinsArray::scan()            strobe row on
                                                        for each readPin
                                                            set rowState bit
                                                    strobe row off
            Debouncer_4Samples::debounce()          debounce
            RowBase::pressRelease()                 for each key in row
                                                        if falling edge
                Key_*::release()                            scanCode->release()
                    Code_*::release()                           Keyboard.release(scancode)
                                                        if rising edge
                Key_*::press()                              scanCode->press()
                    Code_*::press()                             Keyboard.press(scancode)
```

## The Arduino libraries
The keybrd libraries compile on the Arduino IDE and make extensive use of the following [Arduino libraries](https://www.arduino.cc/en/Reference/Libraries):

    #include <Arduino.h>
    #include <Wire.h>
    #include <Keyboard.h>
    #include <Mouse.h>

<a rel="license" href="http://creativecommons.org/licenses/by/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by/4.0/88x31.png" /></a><br /><span xmlns:dct="http://purl.org/dc/terms/" property="dct:title">keybrd guide</span> by <a xmlns:cc="http://creativecommons.org/ns#" href="https://github.com/wolfv6/keybrd" property="cc:attributionName" rel="cc:attributionURL">Wolfram Volpi</a> is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by/4.0/">Creative Commons Attribution 4.0 International License</a>.<br />Permissions beyond the scope of this license may be available at <a xmlns:cc="http://creativecommons.org/ns#" href="https://github.com/wolfv6/keybrd/issues/new" rel="cc:morePermissions">https://github.com/wolfv6/keybrd/issues/new</a>.
