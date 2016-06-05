/* keybrd_single-layer_2_annotated.ino

This sketch:
    is a simple 1-layer keyboard
    runs on the first two rows and columns of a breadboard keyboard
    is annotated with a walk-through narrative

This layout table shows how keys are arranged on the keyboard:

| Layout | **0** | **1** |
|:------:|-------|-------|
|  **0** | a     | b     |
|  **1** | c     | shift |

The layout's row and column numbers are in the headers.
Each cell in the table's body represents a key.

The sketch is annotated with a walk-through narrative enclosed in comment blocks.
Each comment block explains the next one or two lines of code.

keybrd is instantiated under the "GLOBAL" heading.  Most of the sketch is in global space.
keybrd runs at the end of this sketch, under the "MAIN" heading.
*/
// ################## GLOBAL ###################
// ================= INCLUDES ==================
/*
All the includes in this sketch are to keybrd library classes.
*/
//Ports
#include <RowPort_AVR_Optic.h>
#include <ColPort_AVR.h>

//Codes
#include <Code_Sc.h>

//Matrix
#include <Row.h>
#include <Matrix.h>

// ============ SPEED CONFIGURATIONS ============
/*
DELAY_MICROSECONDS specifies the amount of delay between row scans.
Keyboard switches are made of moving contacts.
When the contacts close, they bounce apart one or more times before making steady contact.
DELAY_MICROSECONDS gives the switches time to debounce.

DELAY_MICROSECONDS is a static variable of class Row.
*/
const unsigned int Row::DELAY_MICROSECONDS = 1000;

// =================== PORTS ===================
/*
A micro-controller has one or more ports.  Each port has one or more pins.
These pins are connected to the keyboard's rows and columns.

rowPortF will strobe PORTF one row at a time.
*/
RowPort_AVR_Optic rowPortF(DDRF, PORTF);

/*
A number to the right of "1<<" is a pin number to read.
colPortB will read PORTB's pin 0 and pin 1
*/
ColPort_AVR colPortB(DDRB, PORTB, PINB, 1<<0 | 1<<1 );

/*
ColPort pointers are placed in an array because some keyboards use multiple column ports.
This sketch only has one column port.

sizeof() is used to compute the number of array elements.
This eliminates the risk of forgetting to update the count after adding or removing an element.
*/
ColPort* const ptrsColPorts[] = { &colPortB };
const uint8_t COL_PORT_COUNT = sizeof(ptrsColPorts)/sizeof(*ptrsColPorts);

// =================== CODES ===================
/*
The CODES section instantiates four codes, one for each item in the layout.

The Code_Sc constructor takes one scancode ("Sc" means "scancode").
When Code_Sc is pressed, it sends its scancode.

The Code object names in this sketch start with a "s_" prefix.
*/
Code_Sc s_a(KEY_A);
Code_Sc s_b(KEY_B);
Code_Sc s_c(KEY_C);
Code_Sc s_shift(MODIFIERKEY_LEFT_SHIFT);

// ================== MATRIX ===================
/*
The MATRIX section instantiates the components of the matrix:
    Codes are grouped into rows.
    Rows are grouped into a matrix.

How the matrix works:
 1) The matrix scans one row at a time.
 2) If a row detects a key press, it notifies the code.
 3) The code sends its scancode.
*/
// ------------------- ROWS --------------------
/*
Here we group Code pointers into rows.
Codes are a kind of Key.  Array ptrsKeys_0[] contains two pointers to Key objects.

The Row constructor parameters are:
    one rowPort
    one row pin
    an array of colPorts, and the number of colPorts
    an array of Key pointers

The Row objects names in this sketch start with a "row_" followed by a row number.
*/
Key* const ptrsKeys_0[] = { &s_a, &s_b };
Row row_0(rowPortF, 1<<0, ptrsColPorts, COL_PORT_COUNT, ptrsKeys_0);

Key* const ptrsKeys_1[] = { &s_c,  &s_shift };
Row row_1(rowPortF, 1<<1, ptrsColPorts, COL_PORT_COUNT, ptrsKeys_1);

/*
HOW ROW OBJECTS WORK
When a row is scanned, the row strobes the row pin, and the column ports read their column pins.
If a row detects a key press, it notifies the key which then sends its scancode.
*/

// ------------------ MATRIX -------------------
/*
Here we group Row pointers into a matrix.
Array ptrsRows[] contains two pointers to Row objects.
*/
Row* const ptrsRows[] = { &row_0, &row_1 };
const uint8_t ROW_COUNT = sizeof(ptrsRows)/sizeof(*ptrsRows);

/*
The Matrix constructor parameters are:
    one array of Row pointers
    the number of Row pointers
    '0' for active low or '1' for active high
WARNING: the tutorial sketches all have '1' for active high to be compatible with DH.
The breadboard keyboard described in tutorial_1 is active low.
For active low, change the '1' to a '0':
*/
Matrix matrix(ptrsRows, ROW_COUNT, 1);

// ################### MAIN ####################
/*
Aruduino IDE copies Functions setup() and loop() into main().

setup() initialized the keybrd.
Keyboard.begin() should be called once to initialize.
*/
void setup()
{
    Keyboard.begin();
}

/*
loop() continually scans the Matrix object.
*/
void loop()
{
    matrix.scan();
}
