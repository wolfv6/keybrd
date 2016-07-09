/* keybrd_shift_reg.ino
Tested on Teensy LC and daisy chained 74HC165 shift registers

The keyboard hardware for this sketch has 4 shift registers,
 with every 4th input pin connected to a pull-down resistor and matrix column, also the 31st key.
Unused input pins are not grounded, so add this line to RowScanner_SPIShiftRegisters::scan():
    //clear unpowered pins (for testing on breadboard)
    rowState &= 0b11110001000100010001000100010001; //todo

Layout
| Left  | **0**|**1**| | Right |**0**|**1**|**2**|**3**|**4**|**5**|**6**|**7**|**8**|
|:-----:|------|-----| |:-----:|-----|-----|-----|-----|-----|-----|-----|-----|-----|
| **0** |capLck|  a  | | **0** |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |
| **1** |   b  |  c  | | **1** |  a  |  b  |  c  |  d  |  e  |  f  |  g  |  h  |  i  |
*/
// ################## GLOBAL ###################
// ================= INCLUDES ==================
#include <Debug.h>
#include <ScanDelay.h>
#include <LED_PinNumber.h>

//Codes
#include <Code_Sc.h>
#include <Code_LEDLock.h>

//Matrix
#include <Row_uC.h>
#include <SPI.h>
#include <Row_ShiftRegisters.h>

// =============== CONFIGURATION ===============
ScanDelay scanDelay(9000);
const bool RowScanner_PinsArray::ACTIVE_HIGH = 0; //left matrix is active low
const uint8_t RowScanner_SPIShiftRegisters::SHIFT_LOAD = 10;

Debug debug;

// ================= LEFT PINS =================
uint8_t readPins[] = {14, 15};
uint8_t KEY_COUNT = sizeof(readPins)/sizeof(*readPins);

// ==================== LEDs ===================
LED_PinNumber LED1(16);

//sometimes OS takes 6 seconds to recongnize keyboard, LED blinks from the begining
void wait()
{
    for (uint8_t count = 0; count < 6; count++)
    {
        //print count
        Keyboard.print(count);
        Keyboard.print(F(" "));

        //blink LED
        LED1.on();
        delay(500);
        LED1.off();
        delay(500);
    }
}
// =================== CODES ===================
Code_Sc s_a(KEY_A);
Code_Sc s_b(KEY_B);
Code_Sc s_c(KEY_C);
Code_Sc s_d(KEY_D);
Code_Sc s_e(KEY_E);
Code_Sc s_f(KEY_F);
Code_Sc s_g(KEY_G);
Code_Sc s_h(KEY_H);
Code_Sc s_i(KEY_I);

Code_Sc s_u(KEY_U);
Code_Sc s_v(KEY_V);
Code_Sc s_w(KEY_W);
Code_Sc s_x(KEY_X);

Code_Sc s_z(KEY_Z);

Code_Sc s_0(KEY_0);
Code_Sc s_1(KEY_1);
Code_Sc s_2(KEY_2);
Code_Sc s_3(KEY_3);
Code_Sc s_4(KEY_4);
Code_Sc s_5(KEY_5);
Code_Sc s_6(KEY_6);
Code_Sc s_7(KEY_7);
Code_Sc s_8(KEY_8);

Code_LEDLock o_capsLock(KEY_CAPS_LOCK, LED1);

// ================= LEFT ROWS =================
Key* ptrsKeys_L0[] = { &o_capsLock, &s_a };
Row_uC row_L0(0, readPins, ptrsKeys_L0, KEY_COUNT);

Key* ptrsKeys_L1[] = { &s_b, &s_c };
Row_uC row_L1(1, readPins, ptrsKeys_L1, KEY_COUNT);

// ================= RIGHT ROWS ================
//typedef should be large in /home/wolfv/Documents/Arduino/keybrd_proj/keybrd/src/config_keybrd.h
//Row_ShiftRegisters(STROBE_PIN, ptrsKeys[], KEY_COUNT)
//the s_z are place holders and should not print

/*
//prints 0 1
Key* ptrsKeys_R0[] = { &s_0, &s_z, &s_z, &s_z, &s_1, &s_z, &s_z, &s_z };
const uint8_t KEY_R0_COUNT = sizeof(ptrsKeys_R0)/sizeof(*ptrsKeys_R0);
Row_ShiftRegisters row_R0(8, ptrsKeys_R0, KEY_R0_COUNT);

//prints a b
Key* ptrsKeys_R1[] = { &s_a, &s_z, &s_z, &s_z, &s_b, &s_z, &s_z, &s_z };
const uint8_t KEY_R1_COUNT = sizeof(ptrsKeys_R1)/sizeof(*ptrsKeys_R1);
Row_ShiftRegisters row_R1(9, ptrsKeys_R1, KEY_R1_COUNT);
*/
/*
//prints 0 1 2
Key* ptrsKeys_R0[] = { &s_0, &s_z, &s_z, &s_z, &s_1, &s_z, &s_z, &s_z,
                       &s_2, &s_z, &s_z, &s_z };
const uint8_t KEY_R0_COUNT = sizeof(ptrsKeys_R0)/sizeof(*ptrsKeys_R0);
Row_ShiftRegisters row_R0(8, ptrsKeys_R0, KEY_R0_COUNT);
*/
/*
//prints 0 1 2 3
Key* ptrsKeys_R0[] = { &s_0, &s_z, &s_z, &s_z, &s_1, &s_z, &s_z, &s_z,
                       &s_2, &s_z, &s_z, &s_z, &s_3, &s_z, &s_z, &s_z };
const uint8_t KEY_R0_COUNT = sizeof(ptrsKeys_R0)/sizeof(*ptrsKeys_R0);
Row_ShiftRegisters row_R0(8, ptrsKeys_R0, KEY_R0_COUNT);
*/
/*
//prints 0 1 2 3 4 5
Key* ptrsKeys_R0[] = { &s_0, &s_z, &s_z, &s_z, &s_1, &s_z, &s_z, &s_z,
                       &s_2, &s_z, &s_z, &s_z, &s_3, &s_z, &s_z, &s_z,
                       &s_4, &s_z, &s_z, &s_z, &s_5, &s_z, &s_z, &s_z };
const uint8_t KEY_R0_COUNT = sizeof(ptrsKeys_R0)/sizeof(*ptrsKeys_R0);
Row_ShiftRegisters row_R0(8, ptrsKeys_R0, KEY_R0_COUNT);
*/

//prints 0 1 2 3 3 4 5 6, microseconds_per_scan=87 with SAMPLE_COUNT 4
Key* ptrsKeys_R0[] = { &s_0, &s_z, &s_z, &s_z, &s_1, &s_z, &s_z, &s_z,
                       &s_2, &s_z, &s_z, &s_z, &s_3, &s_z, &s_z, &s_z,
                       &s_4, &s_z, &s_z, &s_z, &s_5, &s_z, &s_z, &s_z,
                       &s_6, &s_z, &s_z, &s_z, &s_3, &s_4, &s_5, &s_6 };
const uint8_t KEY_R0_COUNT = sizeof(ptrsKeys_R0)/sizeof(*ptrsKeys_R0);
Row_ShiftRegisters row_R0(8, ptrsKeys_R0, KEY_R0_COUNT);

//prints a b c d u v w x
Key* ptrsKeys_R1[] = { &s_a, &s_z, &s_z, &s_z, &s_b, &s_z, &s_z, &s_z,
                       &s_c, &s_z, &s_z, &s_z, &s_d, &s_z, &s_z, &s_z,
                       &s_e, &s_z, &s_z, &s_z, &s_f, &s_z, &s_z, &s_z,
                       &s_g, &s_z, &s_z, &s_z, &s_u, &s_v, &s_w, &s_x };
const uint8_t KEY_R1_COUNT = sizeof(ptrsKeys_R1)/sizeof(*ptrsKeys_R1);
Row_ShiftRegisters row_R1(9, ptrsKeys_R1, KEY_R1_COUNT);

// ################### MAIN ####################
void setup()
{
    Keyboard.begin();

    wait();
    SPI.begin();
    row_R0.begin();
    row_R1.begin();

    Keyboard.println(F("keybrd_shift_reg.ino"));
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

//delay(100);
//Keyboard.println("");
//debug.print_microseconds_per_scan();
}
