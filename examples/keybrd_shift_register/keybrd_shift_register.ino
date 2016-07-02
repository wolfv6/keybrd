/* keybrd_shift_reg.ino
tested on Teensy LC and daisy chained 74HC165 shift registers
add this line to RowScanner_SPIShiftRegisters::scan():
    //clear unpowered pins (for testing bb)
    rowState &= 0b01010001000100010001000100010001; //also 31st key

Layout
| Left  |**0**|**1**| | Right |**0**|**1**|**2**|**3**|**4**|**5**|**6**|**7**|**8**|
|:-----:|-----|-----| |:-----:|-----|-----|-----|-----|-----|-----|-----|-----|-----|
| **0** |  a  |  b  | | **0** |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |
| **1** |  c  |  d  | | **1** |  a  |  b  |  c  |  d  |  e  |  f  |  g  |  h  |  i  |
*/
// ################## GLOBAL ###################
// ================= INCLUDES ==================
#include <Debug.h>

//Codes
#include <Code_Sc.h>

//Matrix
#include <Row_uC.h>
#include <SPI.h>
#include <Row_ShiftRegisters.h>

// =============== CONFIGURATION ===============
const unsigned int RowBase::DELAY_MICROSECONDS = 500; //500
const uint8_t RowScanner_SPIShiftRegisters::SHIFT_LOAD = 10;

//activeLow  has diode cathode (band) on row
//activeHigh has diode cathode (band) on col, and pull down resistors on cols
//0=active low, 1= active high
const bool RowScanner_PinsArray::ACTIVE_HIGH = 0;

Debug debug;

// ================= LEFT PINS =================
uint8_t readPins[] = {14, 15};
uint8_t READ_PIN_COUNT = sizeof(readPins)/sizeof(*readPins);

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

Code_Sc s_0(KEY_0);
Code_Sc s_1(KEY_1);
Code_Sc s_2(KEY_2);
Code_Sc s_3(KEY_3);
Code_Sc s_4(KEY_4);
Code_Sc s_5(KEY_5);
Code_Sc s_6(KEY_6);
Code_Sc s_7(KEY_7);
Code_Sc s_8(KEY_8);
Code_Sc s_z(KEY_Z);

// ================= LEFT ROWS =================
Key* ptrsKeys_L0[] = { &s_a, &s_b };
Row_uC row_L0(0, readPins, READ_PIN_COUNT, ptrsKeys_L0);

Key* ptrsKeys_L1[] = { &s_c, &s_d };
Row_uC row_L1(1, readPins, READ_PIN_COUNT, ptrsKeys_L1);

// ================= RIGHT ROWS ================
//typedef should be large in /home/wolfv/Documents/Arduino/keybrd_proj/keybrd/src/config_keybrd.h
//Row_ShiftRegisters(STROBE_PIN, ptrsKeys[], KEY_COUNT)
//the s_z are place holders and should not print

//prints 0 1
Key* ptrsKeys_R0[] = { &s_0, &s_z, &s_z, &s_z, &s_1, &s_z, &s_z, &s_z };
const uint8_t KEY_R0_COUNT = sizeof(ptrsKeys_R0)/sizeof(*ptrsKeys_R0);
Row_ShiftRegisters row_R0(8, ptrsKeys_R0, KEY_R0_COUNT);

//prints a b
Key* ptrsKeys_R1[] = { &s_a, &s_z, &s_z, &s_z, &s_b, &s_z, &s_z, &s_z };
const uint8_t KEY_R1_COUNT = sizeof(ptrsKeys_R1)/sizeof(*ptrsKeys_R1);
Row_ShiftRegisters row_R1(9, ptrsKeys_R1, KEY_R1_COUNT);
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

/*
//prints 0 1 2 3 4 5 6 7 8
Key* ptrsKeys_R0[] = { &s_0, &s_z, &s_z, &s_z, &s_1, &s_z, &s_z, &s_z,
                       &s_2, &s_z, &s_z, &s_z, &s_3, &s_z, &s_z, &s_z,
                       &s_4, &s_z, &s_z, &s_z, &s_5, &s_z, &s_z, &s_z,
                       &s_6, &s_z, &s_z, &s_z, &s_7, &s_z, &s_8 }; //31-key limit because endRow
const uint8_t KEY_R0_COUNT = sizeof(ptrsKeys_R0)/sizeof(*ptrsKeys_R0);
Row_ShiftRegisters row_R0(8, ptrsKeys_R0, KEY_R0_COUNT);

//prints a b c d e f g h i
Key* ptrsKeys_R1[] = { &s_a, &s_z, &s_z, &s_z, &s_b, &s_z, &s_z, &s_z,
                       &s_c, &s_z, &s_z, &s_z, &s_d, &s_z, &s_z, &s_z,
                       &s_e, &s_z, &s_z, &s_z, &s_f, &s_z, &s_z, &s_z,
                       &s_g, &s_z, &s_z, &s_z, &s_h, &s_z, &s_i }; //31-key limit because endRow
const uint8_t KEY_R1_COUNT = sizeof(ptrsKeys_R1)/sizeof(*ptrsKeys_R1);
Row_ShiftRegisters row_R1(9, ptrsKeys_R1, KEY_R1_COUNT);
*/

const uint8_t LED_PIN = 16;                     //indicates wait

//sometimes OS takes 6 seconds to recongnize keyboard, LED blinks from the begining
void wait()
{
    for (uint8_t count = 0; count < 6; count++)
    {
        //print count
        Keyboard.print(count);
        Keyboard.print(F(" "));

        //blink LED
        digitalWrite(LED_PIN, HIGH);
        delay(900);
        digitalWrite(LED_PIN, LOW);
        delay(100);
    }
}
// ################### MAIN ####################
void setup()
{
    pinMode (LED_PIN, OUTPUT);
    Keyboard.begin();
    SPI.begin();
    row_R0.begin();
    row_R1.begin();

    wait();
    Keyboard.print(F("keybrd_shift_reg.ino "));
    debug.print_free_RAM();
}

void loop()
{
    row_L0.process();
    row_L1.process();

    row_R0.process();
    row_R1.process();

//delay(100);
//Keyboard.println("");
//debug.print_microseconds_per_scan();
}
