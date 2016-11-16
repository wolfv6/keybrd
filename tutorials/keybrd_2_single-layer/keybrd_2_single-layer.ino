/* keybrd_2_single-layer.ino

This sketch:
    is firmware for a simple 1-layer keyboard
    runs on two rows and two columns of a breadboard keyboard

This layout table shows how keys are arranged on the keyboard:

| Layout | **0** | **1** |
|:------:|-------|-------|
|  **0** |   1   |   2   |
|  **1** |   a   |   b   |

The layout's row and column numbers are in the headers.
Each cell in the table's body represents a key.

The following sketch is annotated with a walk-through narrative enclosed in comment blocks.
Each comment block explains one or two lines of code after the comnent.

keybrd objects are instantiated under the "GLOBAL" heading.
The keyboard runs at the end of the sketch, under the "MAIN" heading.
*/
// ################## GLOBAL ###################
/* ================= INCLUDES ==================
All the includes in this sketch are to keybrd library classes.
*/
#include <Code_Sc.h>
#include <Row.h>
#include <Scanner_uC.h>
#include <ScanDelay.h>

/* ============ SPEED CONFIGURATION ============
Keyboard switches are made of moving contacts.
When the contacts close, they bounce apart one or more times before making steady contact.
ScanDelay gives the switches time to debounce.
ScanDelay specifies microsecond between matrix scans.
*/
ScanDelay scanDelay(9000);

/* ================== SCANNER ==================
Microcontroller pins 14 and 15 are connected to the matrix columns.
sizeof() is used to compute the number of array elements.
This eliminates the risk of a programmer forgetting to update a count
after adding or removing an element from the array.
*/
uint8_t readPins[] = {14, 15};
uint8_t readPinCount = sizeof(readPins)/sizeof(*readPins);

/*
Scanner_uC constructor parameters are: activeState, readPins[], readPinCount.
activeState defines the logic level for strobes, HIGH or LOW.
"Active low" means that if a switch is pressed (active), the read pin is low.
The scanner uses readPins and readPinCount to read the colums.
*/
Scanner_uC scanner(LOW, readPins, readPinCount);

/* HOW SCANNER OBJECTS WORK
The Scanner object strobes a row.
If a key is pressed, the LOW strobe pulls that readPin LOW.
Then the scanner reads its readPins.
*/

/* =================== CODES ===================
Four Codes are instantiated, one for each key in the layout.
The Code object names in this sketch start with a "s_" prefix.

The Code_Sc constructor takes one scancode ("Sc" means "scancode").
When Code_Sc is pressed, it sends the scancode.
*/
Code_Sc s_a(KEY_A);
Code_Sc s_b(KEY_B);

Code_Sc s_1(KEY_1);
Code_Sc s_2(KEY_2);

/* =================== ROWS ====================
Here we pack Code objects into Row objects.
The Row objects names in this sketch start with a "row_" followed by a row number.

Row constructor parameters are: scanner, strobePin, ptrsKeys[], keyCount.
strobePin is the Arduino pin number connected to the row.
ptrsKeys[] contains all the Code objects of the row, one Code object per key.
*/
Key* ptrsKeys_0[] = { &s_1, &s_2 };
uint8_t keyCount_0 = sizeof(ptrsKeys_0)/sizeof(*ptrsKeys_0);
Row row_0(scanner, 0, ptrsKeys_0, keyCount_0);

Key* ptrsKeys_1[] = { &s_a, &s_b };
uint8_t keyCount_1 = sizeof(ptrsKeys_1)/sizeof(*ptrsKeys_1);
Row row_1(scanner, 1, ptrsKeys_1, keyCount_1);

/* ################### MAIN ####################
setup() is used to initialize the keyboard firmware.  Keyboard.begin() should be called once.
*/
void setup()
{
    Keyboard.begin();
}

/*
loop() continually scans the matrix, one row at a time.
Each Row object strobes its strobePin and reads the readPins.
And when a key press is detected, the row sends the key's scancode.

scanDelay creates time intervals between matrix scans.
The delay is needed so that the debouncer is not overwelmed.
*/
void loop()
{
    row_0.process();
    row_1.process();
    scanDelay.delay();
}
