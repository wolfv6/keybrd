/* keybrd_2_single-layer.ino

This sketch:
    is firmware for a simple 1-layer keyboard
    runs on the first two rows and columns of a breadboard keyboard

This layout table shows how keys are arranged on the keyboard:

| Layout | **0** | **1** |
|:------:|-------|-------|
|  **0** | shift | a     |
|  **1** | b     | c     |

The layout's row and column numbers are in the headers.
Each cell in the table's body represents a key.

The following sketch is annotated with a walk-through narrative enclosed in comment blocks.
Each comment block explains the next one or two lines of code.

keybrd objects are instantiated under the "GLOBAL" heading.
The keyboard runs at the end of the sketch, under the "MAIN" heading.
*/
// ################## GLOBAL ###################
/* ================= INCLUDES ==================
All the includes in this sketch are to keybrd library classes.
*/
#include <ScanDelay.h>
#include <Code_Sc.h>
#include <Row_uC.h>

/* ============ SPEED CONFIGURATION ============
ScanDelay specifies microsecond between matrix scans.
Keyboard switches are made of moving contacts.
When the contacts close, they bounce apart one or more times before making steady contact.
ScanDelay gives the switches time to debounce.
*/
ScanDelay scanDelay(9000);

/* ================ ACTIVE STATE ===============
The read pins detect which keys are pressed while a row is strobed.
STROBE_ON and STROBE_OFF define the logic levels for the strobe.
"Active low" means that if a switch is pressed (active), the read pin is low.
To make this sketch active low, STROBE_ON should be LOW (tutorial 6 coveres this in more detail).
*/
const bool Scanner_uC::STROBE_ON = LOW; //set scanner for active low
const bool Scanner_uC::STROBE_OFF = HIGH;

/* ================= PINS =================
Micro-controller 14 and 15 are connected to the matrix columns.
These readPins detect which keys are pressed while a row is strobed.

sizeof() is used to compute the number of array elements.
This eliminates the risk of forgetting to update the count
after adding or removing an element from the array.
*/
uint8_t readPins[] = {14, 15};
uint8_t READ_PIN_COUNT = sizeof(readPins)/sizeof(*readPins);

/* =================== CODES ===================
Four Codes are instantiated, one for each key in the layout.
The Code object names in this sketch start with a "s_" prefix.

The Code_Sc constructor takes one scancode ("Sc" means "scancode").
When Code_Sc is pressed, it sends the scancode.
*/
Code_Sc s_a(KEY_A);
Code_Sc s_b(KEY_B);
Code_Sc s_c(KEY_C);
Code_Sc s_shift(MODIFIERKEY_LEFT_SHIFT);

/* =================== ROWS ====================
Here we pack Code objects into Row objects.
The Row objects names in this sketch start with a "row_" followed by a row number.

Row_uC constructor has four parameters:
 1) strobePin connected to the row.
 2) readPins[] connected to the colums.
 3) the number of readPins.
 4) ptrsKeys[] containing all the Code objects of the row, one Code object per key.

*/
Key* ptrsKeys_0[] = { &s_shift, &s_a };
Row_uC row_0(0, readPins, READ_PIN_COUNT, ptrsKeys_0);

Key* ptrsKeys_1[] = { &s_b, &s_c  };
Row_uC row_1(1, readPins, READ_PIN_COUNT, ptrsKeys_1);

/* ################### MAIN ####################
setup() is used to initialize the keyboard firmware.  Keyboard.begin() should be called once.
*/
void setup()
{
    Keyboard.begin();
}

/*
loop() continually scans the matrix, one row at a time.
Each row object strobes its strobePin and reads the readPins.
And when a key press is detected, the row sends the key's scancode.

scanDelay creates time intervals between matrix scans.
A debouncer uses this time interval to debounce key presses and releases.
*/
void loop()
{
    row_0.process();
    row_1.process();
    scanDelay.delay();
}
