/* tutorial_4a_split_keyboard_with_shift_registers.ino
Tested on Teensy LC and two 74HC165 shift registers.

The right matrix has 2 shift registers daisy chained.

  Layout          Layout
| Left  |**0**| | Right |**0**|**1**|**2**|**3**|**4**|**5**|**6**|
|:-----:|-----| |:-----:|-----|-----|-----|-----|-----|-----|-----|
| **0** |  x  | | **0** |  0  |  1  |  2  |  3  |  4  |  5  |  6  |
| **1** |  y  | | **1** |  a  |  b  |  c  |  d  |  e  |  f  |  g  |
*/
// ################## GLOBAL ###################
// ================= INCLUDES ==================
#include <ScanDelay.h>
#include <Code_Sc.h>

//Left matrix
#include <Scanner_uC.h>
#include <Row.h>

//Right matrix
#include <SPI.h>//needed?? todo
#include <Scanner_ShiftRegs74HC165.h>

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
uint8_t readPins_L[] = {14};
uint8_t readPinCount_L = sizeof(readPins_L)/sizeof(*readPins_L);

Scanner_uC scanner_L(LOW, readPins_L, readPinCount_L); //active LOW

//rows
Key* ptrsKeys_L0[] = { &s_x };
uint8_t KEY_COUNT_L0 = sizeof(ptrsKeys_L0)/sizeof(*ptrsKeys_L0);
Row row_L0(scanner_L, 0, ptrsKeys_L0, KEY_COUNT_L0);

Key* ptrsKeys_L1[] = { &s_y };
uint8_t KEY_COUNT_L1 = sizeof(ptrsKeys_L1)/sizeof(*ptrsKeys_L1);
Row row_L1(scanner_L, 1, ptrsKeys_L1, KEY_COUNT_L1);

// =============== RIGHT MATRIX ================
//use slaveSelect pin SS (Arduino pin 10) for fastest scan
Scanner_ShiftRegs74HC165 scanner_R(HIGH, SS, 14); //active HIGH

//rows
Key* ptrsKeys_R0[] = { &s_6, &s_5, &s_4, &s_3,  //shift register on right
                       &s_c, &s_d, &s_e, &s_f,
                       &s_2, &s_1, &s_0, &s_g,  //shift register on left
                       &s_a, &s_b };            //unused input pins are grounded
Row row_R0(scanner_R, 0, ptrsKeys_R0, sizeof(ptrsKeys_R0)/sizeof(*ptrsKeys_R0));

// ################### MAIN ####################
void setup()
{
    Keyboard.begin();
    SPI.begin();//todo move to begin()
    scanner_R.begin();
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
