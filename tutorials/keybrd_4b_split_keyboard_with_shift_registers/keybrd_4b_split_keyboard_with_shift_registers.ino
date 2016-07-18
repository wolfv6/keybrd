/* tutorial_4a_split_keyboard_with_shift_registers.ino
Tested on Teensy LC and two 74HC165 shift registers.

The right matrix has 2 shift registers daisy chained.
Every 4th input pin has a pull-up resistor and matrix column.
Unused input pins are powered.

  Layout           Layout
| Left  | **0**| | Right |**0**|**1**|**2**|**3**|
|:-----:|------| |:-----:|-----|-----|-----|-----|
| **0** |   x  | | **0** |  0  |  1  |  2  |  3  |
| **1** |   y  | | **1** |  a  |  b  |  c  |  d  |
*/
// ################## GLOBAL ###################
// ================= INCLUDES ==================
//Codes
#include <Code_Sc.h>
#include <Code_LEDLock.h>

//Matrix
#include <SPI.h>
#include <Row_uC.h>
#include <Row_ShiftRegisters.h>
#include <ScanDelay.h>

// =============== CONFIGURATION ===============
ScanDelay scanDelay(9000);

//set left matrix for active low
const bool Scanner_uC::STROBE_ON = LOW;
const bool Scanner_uC::STROBE_OFF = HIGH;

const uint8_t Scanner_ShiftRegs74HC165::SHIFT_LOAD = 10;

//set right matrix for active low
const bool Scanner_ShiftRegs74HC165::STROBE_ON = LOW;
const bool Scanner_ShiftRegs74HC165::STROBE_OFF = HIGH;

// ================= LEFT PINS =================
uint8_t readPins[] = {14};
uint8_t READ_PIN_COUNT = sizeof(readPins)/sizeof(*readPins);

// =================== CODES ===================
Code_Sc s_a(KEY_A);
Code_Sc s_b(KEY_B);
Code_Sc s_c(KEY_C);
Code_Sc s_d(KEY_D);

Code_Sc s_x(KEY_X);
Code_Sc s_y(KEY_Y);

Code_Sc s_z(KEY_Z);

Code_Sc s_0(KEY_0);
Code_Sc s_1(KEY_1);
Code_Sc s_2(KEY_2);
Code_Sc s_3(KEY_3);

// ================= LEFT ROWS =================
Key* ptrsKeys_L0[] = { &s_x };
Row_uC row_L0(0, readPins, READ_PIN_COUNT, ptrsKeys_L0);

Key* ptrsKeys_L1[] = { &s_y };
Row_uC row_L1(1, readPins, READ_PIN_COUNT, ptrsKeys_L1);

/* ================= RIGHT ROWS ================
Instantiating a Row_ShiftRegistersis similar to instantiating a Row_uC.

The s_z are place holders where the input pins are powered; they should not send scancodes.
*/

//should send 0 1 2 3
Key* ptrsKeys_R0[] = { &s_0, &s_z, &s_z, &s_z, &s_1, &s_z, &s_z, &s_z,
                       &s_2, &s_z, &s_z, &s_z, &s_3, &s_z, &s_z, &s_z };
Row_ShiftRegisters row_R0(0, sizeof(ptrsKeys_R0)/sizeof(*ptrsKeys_R0), ptrsKeys_R0);

//should send a b c d
Key* ptrsKeys_R1[] = { &s_a, &s_z, &s_z, &s_z, &s_b, &s_z, &s_z, &s_z,
                       &s_c, &s_z, &s_z, &s_z, &s_d, &s_z, &s_z, &s_z };
Row_ShiftRegisters row_R1(1, sizeof(ptrsKeys_R1)/sizeof(*ptrsKeys_R1), ptrsKeys_R1);

// ################### MAIN ####################
void setup()
{
    Keyboard.begin();
    SPI.begin();
    row_R0.begin();
    row_R1.begin();
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
}
