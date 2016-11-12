/* keybrd_MCP23018.ino

This sketch:
    is a simple 1-layer keyboard
    runs on two matrices of a breadboard keyboard

  Controller                I/O expander
| Left  | **0** | **1** | | Right | **0** | **1** |
|-------|-------|-------| |-------|-------|-------|
| **1** |   1   |   2   | | **1** |   3   |   4   |
| **0** |   a   |   b   | | **0** |   c   |   d   |
*/
// ################## GLOBAL ###################
// ================= INCLUDES ==================
#include <ScanDelay.h>
#include <Code_Sc.h>
#include <Code_LEDLock.h>
#include <Row.h>

//left matrix
#include <Scanner_uC.h>

//right matrix
#include <Port_MCP23018.h>
#include <Scanner_IOE.h>
#include <LED_Port.h>

// ============ SPEED CONFIGURATION ============
ScanDelay scanDelay(9000);

/* ================ LEFT SCANNER ===============
Left matrix rows work the same as the ones in keybrd_2_single-layer.ino
*/
uint8_t readPins[] = {14, 15};
const uint8_t readPinCount = sizeof(readPins)/sizeof(*readPins);

Scanner_uC scanner_L(LOW, readPins, readPinCount);

/* =============== RIGHT SCANNER ===============
The right matrix is scanned by an I/O expander.
The MCP23018 address is set by grounding or powering pins.
*/
const uint8_t IOE_ADDR = 0x20;                  //MCP23018 address pin grounded

/*
Normally all strobe pins are on one port, and all the read pins are on the other port.
In this example, portB stobes the row while portA reads the colums.
Port_MCP23018 constructor parameters are: deviceAddr, portNum, readPins.
readPins is a bit pattern, where 0=output, 1=input.
In portA, the first two pins are set to input for reading.
"<<" (bit shift left) and "|" (OR) are bitwise operators.
Pin numbers to be read are delimited by "|" and to the right of "1<<".
*/
Port_MCP23018 portA(IOE_ADDR, 0, 1<<0 | 1<<1 ); //read pins 0, 1
Port_MCP23018 portB(IOE_ADDR, 1, 0);
Scanner_IOE scanner_R(LOW, portB, portA);

/* ================= RIGHT LED =================
The LED_Port constructor parameters are a port and pin number that is connected to an LED.
*/
LED_Port LED_capsLck(portA, 1<<7);

// =================== CODES ===================
Code_Sc s_a(KEY_A);
Code_Sc s_b(KEY_B);
Code_Sc s_c(KEY_C);
Code_Sc s_d(KEY_D);

Code_Sc s_1(KEY_1);
Code_Sc s_2(KEY_2);
Code_Sc s_3(KEY_3);
Code_Sc s_4(KEY_4);

Code_LEDLock o_capsLock(KEY_CAPS_LOCK, LED_capsLck);//was testing LED, restore s_4 when done

/* =================== ROWS ====================
Left row names contain the letter 'L', while right row names conatain the letter 'R'.

Row constructor parameters are: scanner, strobePin, ptrsKeys[], keyCount.
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
Key* ptrsKeys_R0[] = { &s_3, &o_capsLock };
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
    //debug.printScansPerSecond();
    //debug.printMicrosecondsPerScan();
}
