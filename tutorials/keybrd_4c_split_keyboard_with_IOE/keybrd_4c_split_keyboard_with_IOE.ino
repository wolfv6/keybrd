/* keybrd_4c_split_keyboard_with_IOE.ino

This sketch:
    is a simple 1-layer keyboard
    runs on two matrices of a breadboard keyboard

This layout table shows left and right matrices:

| Left  | **0** | **1** | | Right | **0** | **1** |
|:-----:|-------|-------|-|:-----:|-------|-------|
| **1** |   1   |   2   | | **1** |   3   |   4   |
| **0** |   a   |   b   | | **0** |   c   |   d   |
*/
// ################## GLOBAL ###################
// ================= INCLUDES ==================
#include <ScanDelay.h>
#include <Code_Sc.h>
#include <Row.h>

//left matrix
#include <Scanner_uC.h>

//right matrix
#include <PortIOE.h>
#include <PortWrite_MCP23S17.h>
#include <PortRead_MCP23S17.h>
#include <Scanner_IOE.h>

// ============ SPEED CONFIGURATION ============
ScanDelay scanDelay(9000);

/* ================ LEFT SCANNER ===============
Left matrix rows work the same as the ones in keybrd_2_single-layer.ino
*/
uint8_t readPins[] = {14, 15};
const uint8_t READPIN_COUNT = sizeof(readPins)/sizeof(*readPins);

Scanner_uC scanner_L(LOW, readPins, READPIN_COUNT);

/* =============== RIGHT SCANNER ===============
The right matrix is scanned by an I/O expander.

The I/O expander device address is configured by hardware pins.
DEVICE_ADDR is a static variable of class PortIOE.
*/
const uint8_t PortIOE::DEVICE_ADDR = 0x20;      //MCP23S17 address with all 3 ADDR pins are grounded

/*
port_B stobes the row while port_A reads the colums.

port_A is assigned port identification number 0.
port_A is assigned to portRead, which reads port_A pins 0 and 1.
"<<" (bit shift left) and "|" (OR) are bitwise operators.
Pin numbers to be read are to the right of "1<<" and delimited by "|".
*/
PortIOE port_A(0);
PortRead_MCP23S17 portRead(port_A, 1<<0 | 1<<1 );

/*
port_B is assigned port identification number 1.
port_B is assigned to portWrite.
*/
PortIOE port_B(1);
//PortWrite_MCP23S17 portWrite(port_B);     //for LEDs todo
PortWrite_MCP23S17 portWrite(port_B);

Scanner_IOE scanner_R(LOW, portWrite, portRead);

// =================== CODES ===================
Code_Sc s_a(KEY_A);
Code_Sc s_b(KEY_B);
Code_Sc s_c(KEY_C);
Code_Sc s_d(KEY_D);

Code_Sc s_1(KEY_1);
Code_Sc s_2(KEY_2);
Code_Sc s_3(KEY_3);
Code_Sc s_4(KEY_4);

/* =================== ROWS ====================
Left row names contain the letter 'L', while right row names conatain the letter 'R'.

The first parameteer of a Row constructor specifies the scanner.
The second parameter of the Row constructor specifies the Row's strobePin.
strobePin has one of two formats:
 * if refScanner a Scanner_uC, then strobePin is an Arduino pin number connected to this row
 * otherwise strobePin is a bit pattern, 1 indicating an IC pin connected to the row
*/
/* ---------------- LEFT ROWS ------------------
The left rows have a Scanner_uC and Arduino pin numbers to strobe.
*/
Key* ptrsKeys_L0[] = { &s_1, &s_2 };
const uint8_t KEY_COUNT_L0 = sizeof(ptrsKeys_L0)/sizeof(*ptrsKeys_L0);
Row row_L0(scanner_L, 0, ptrsKeys_L0, KEY_COUNT_L0);

Key* ptrsKeys_L1[] = { &s_a, &s_b };
const uint8_t KEY_COUNT_L1 = sizeof(ptrsKeys_L1)/sizeof(*ptrsKeys_L1);
Row row_L1(scanner_L, 1, ptrsKeys_L1, KEY_COUNT_L1);

/* ---------------- RIGHT ROWS -----------------
The right rows have a Scanner_IOE and pin bits to strobe.
*/
Key* ptrsKeys_R0[] = { &s_3, &s_4 };
const uint8_t KEY_COUNT_R0 = sizeof(ptrsKeys_R0)/sizeof(*ptrsKeys_R0);
Row row_R0(scanner_R, 1<<0, ptrsKeys_R0, KEY_COUNT_R0);

Key* ptrsKeys_R1[] = { &s_c,  &s_d };
const uint8_t KEY_COUNT_R1 = sizeof(ptrsKeys_R1)/sizeof(*ptrsKeys_R1);
Row row_R1(scanner_R, 1<<1, ptrsKeys_R1, KEY_COUNT_R1);

// ################### MAIN ####################
void setup()
{
    Keyboard.begin();
    scanner_R.begin();
}

void loop()
{
    //left matrix
    row_L0.process();
    row_L1.process();

    //right matrix
    row_R0.process();
    row_R1.process();

    scanDelay.delay();
    //debug.print_scans_per_second();
    //debug.print_microseconds_per_scan();
}
