keybrd Library Developer's Guide
================================
This guide contains diagrams, naming conventions, and a style guide,
 which are useful when designing new classes for the keybrd library and its extension libraries.
The most common reason for new classes are:
* Port classes for micro controller or I/O expanders
* custom layer schemes for multi-layer keyboards
* experimental features

## Who this guide is for
This guide is for the maintainers and developers of the keybrd library and it's extensions.
It is assumed the reader is familiar with C++ language including pointers, objects, classes, static class variables, composition, inheritance, polymorphism, and enum.
Some classes use bit manipulation.

## Class diagrams

Keybrd library class inheritance diagram
```
	Matrix

	Row

	IOExpanderPort

	         _______ RowPort _______
	        /          |            \
	RowPort_AVR  RowPort_MCP23018  RowPort_PCA9655E     (one RowPort class for each type of IC)
 
	          _______ ColPort _______
	         /          |            \
	ColPort_AVR  ColPort_MCP23018  ColPort_PCA9655E     (one ColPort class for each type of IC)
 
	       _____ LED ______
	      /       |        \
	LED_AVR  LED_MCP23018  LED_PCA9655E                 (one LED class for each type of IC)


	StateLayersInterface
	    |
	StateLayers


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
	     Code_Sc  Code_Shift  Code_AutoShift  Code_LockLED
	                         /      |      \
	                  Code_ScS  Code_ScNS  Code_ScNS_00

```

## Association diagrams

single-layer Keybrd association diagram with LEDs
```
	keybrd[1]
	  |
	matrix[1..*]
	  |
	row[1..*]_____________________________
	  |          \          \             \
	rowPort[1]  rowPin[1]  colPort[1]     keys[1]
	                         |             |
	                       colPins[1..*]  code[1..*]
	                                       |
	                                      LED[1]

```

multi-layer Keybrd association diagram with LEDs and I/O Expander
```

	keybrd[1]
	  |
	matrix[1..*]
	  |                                                stateLayers[1..*]
	row[1..*]_________________________________________/__    |         \
	  |          \          \                \       /   \   |          \
	rowPort[1]  rowPin[1]  colPort[1]       keys[1] / code_layer[1..*]  LED[0..*]
	   \                  /   \               |    /                    /
	    \                /   colPins[1..*]  key[1..*]                  /
	     \              /                     |                       /
	      \            /                    code[1..*]               /
	       \          /       ______________________________________/
	      IOExpanderPort[0..*] 

```

## Class naming conventions
Class names start with upper case letter.
Most derived-class names start with the base class name followed by "_" and a name e.g.
```
	Code
	  |
	Code_Sc

```
This convention leads to class names that convey information about the classes inheritance.
Underscore delineates base class name and sub-class name.  Capital letters delineate words.

## Style guide
Following the style guide makes it easier for the next programmer to understand your code.
* For class names, see above section "Class naming conventions"
* For member names, use camelCase starting with lowercase letter.
* Use constants rather than macros, except for header guards.
* For constant names that could be macros, use ALL_CAPS_AND_UNDERSCORE.
    * **ITEM_COUNT** is a constant number of items.
    * **itemCount** is a variable number of items.
* Use header guards CLASS_NAME_H.
* Prefix pointer name with "ptr" e.g. ptrRow =  &row
* Name arrays using the plural of element name e.g. Row* const = ptrsRows { &row0,  &row1 };
* Pass arrays using array notation rather than pointer notation.  Use
```
        void printArray(char[] array);
    not
        void printArray( char* array);
```
* In constructor's initialization list, use same names for fields and constructor parameters.
* Do not use new or malloc (making memory leaks impossible).
* If class has any non-[POD](http://en.wikipedia.org/wiki/Plain_old_data_structure) data members, [do not inline constructors and destructors](http://www.chromium.org/developers/coding-style/cpp-dos-and-donts).
* Document class interface in .h file, above the class declaration.
* Code should be self-documenting.  The only comments should be things that may need clarification.  A simple function with a good name needs no comment.
* Code is automatically formated before being pushed to the keybrd repository
  The options file doc/astyle_cpp specifies the format:
    * Allman style indentation
    * indent 4 spaces
    * replace tabs with spaces
    * maximum code width of 100 columns

  <!-- http://stackoverflow.com/questions/2198241/best-practice-for-c-function-commenting -->

## Trace of keybrd scan
Arduino does not have a debugger; so here is a list of functions in the order that they are called.
Refer to it like a table of contents while reading the keybrd library.

```
Keybrd::scan()                          for each matrix
    Matrix::scan()                          for each row
        Row::process()
            Row::scan()
                RowPort_*::setActivePin*()      strobe row on
                                                for each col port
                    ColPort_*::read()               read col port
                RowPort_*::setActivePin*()      strobe row off
            Row::getRowState()                  for each col port
                                                    for each connected col pin
                                                        if key is pressed
                                                            set rowState bit
            Row::debounce()                     debounce
            Row::detectEdge()                   detect edge
            Row::pressRelease()                 for each key in row
                                                    if rising edge
                Key_*::press()                          scanCode->press()
                    Code_*::press()                         Keyboard.press(scancode)
```

## The Arduino libraries
The keybrd libraries compile on the Arduino IDE and make extensive use of the following [Arduino libraries](https://www.arduino.cc/en/Reference/Libraries):

    #include <Arduino.h>
    #include <Wire.h>
    #include <Keyboard.h>
    #include <Mouse.h>
