/* tutorial_4a_split_keyboard_with_shift_registers.ino
Tested on Teensy LC and two 74HC165 shift registers.

The right matrix has 2 shift registers daisy chained.

  Layout          Layout
| Left  |**0**  | Right |**0**|**1**|**2**|**3**|**4**|**5**|**6**|**7**|
|:-----:|-----| |:-----:|-----|-----|-----|-----|-----|-----|-----|-----|
| **0** |  x  | | **0** |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |
| **1** |  y  | | **1** |  a  |  b  |  c  |  d  |  e  |  f  |  g  |  h  |
*/
// ################## GLOBAL ###################
// ================= INCLUDES ==================
#include <ScanDelay.h>
#include <Code_Sc.h>

//Left matrix
#include <Row_uC.h>

//Right matrix
#include <SPI.h>
#include <Row_ShiftRegisters.h>

// =============== CONFIGURATION ===============
ScanDelay scanDelay(9000);

// =================== CODES ===================
Code_Sc s_a(KEY_A);
Code_Sc s_b(KEY_B);
Code_Sc s_c(KEY_C);
Code_Sc s_d(KEY_D);
Code_Sc s_e(KEY_E);
Code_Sc s_f(KEY_F);
Code_Sc s_g(KEY_G);

Code_Sc s_x(KEY_X);
Code_Sc s_y(KEY_Y);

Code_Sc s_0(KEY_0);
Code_Sc s_1(KEY_1);
Code_Sc s_2(KEY_2);
Code_Sc s_3(KEY_3);
Code_Sc s_4(KEY_4);
Code_Sc s_5(KEY_5);
Code_Sc s_6(KEY_6);

// =============== LEFT MATRIX =================
//set left matrix for active low
const bool Scanner_uC::STROBE_ON = LOW;
const bool Scanner_uC::STROBE_OFF = HIGH;

//column pin
uint8_t readPins[] = {14};
uint8_t READ_PIN_COUNT = sizeof(readPins)/sizeof(*readPins);

//rows
Key* ptrsKeys_L0[] = { &s_x };
Row_uC row_L0(0, readPins, READ_PIN_COUNT, ptrsKeys_L0);

Key* ptrsKeys_L1[] = { &s_y };
Row_uC row_L1(1, readPins, READ_PIN_COUNT, ptrsKeys_L1);

// =============== RIGHT MATRIX ================
//set matrix to active high
const bool Scanner_ShiftRegs74HC165::STROBE_ON = HIGH;
const bool Scanner_ShiftRegs74HC165::STROBE_OFF = LOW;

//chip select pin
const uint8_t Scanner_ShiftRegs74HC165::SHIFT_LOAD = 10;

//rows
Key* ptrsKeys_R0[] = { &s_6, &s_5, &s_4, &s_3,  //shift regiser on right
                       &s_c, &s_d, &s_e, &s_f,
                       &s_2, &s_1, &s_0, &s_g,  //shift regiser on left
                       &s_a, &s_b };            //unused input pins are grounded
Row_ShiftRegisters row_R0(0, sizeof(ptrsKeys_R0)/sizeof(*ptrsKeys_R0), ptrsKeys_R0);

// ################### MAIN ####################
void setup()
{
    Keyboard.begin();
    SPI.begin();
    row_R0.begin();
}

void loop()
{
    //left matrix
    row_L0.process();
    row_L1.process();

    //right matrix
    row_R0.process();

    scanDelay.delay();
}
