/* this works on DH 4*bb, top-left buttons
demo RowScanner_PinsBitwise

| Left  | **0** | **1** |  | Right | **0** | **1** |
|:-----:|-------|-------|  |:-----:|-------|-------|
| **0** | a     | b     |  | **0** | 0     | 1     |
| **1** | c     | d     |  | **1** | 2     | 3     |
*/
// ################## GLOBAL ###################
// ================= INCLUDES ==================
#include <Debug.h>

//Ports
#include <RowPort_AVR_Optic.h>
#include <ColPort_AVR.h>

//LEDs
#include <LED_AVR.h>
#include <LED_PCA9655E.h>
#include "classes/Code_Sc_LED.h"                //symlink: ln -s ../classes classes

//Codes
#include <Code_Sc.h>

//Matrix
#include <Row_IOE.h>
#include <Matrix.h>

// =============== CONFIGURATION ===============
const unsigned int RowBase::DELAY_MICROSECONDS = 500;

const bool RowScanner_PinsBitwise::activeHigh = 1;

Debug debug;

// ================ LEFT PORTS =================
RowPort_AVR_Optic rowPort_L(DDRF, PORTF);
ColPort_AVR colPort_L(DDRB, PORTB, PINB, 1<<0 | 1<<1 );

//LED
LED_AVR LED_L1(PORTB, 1<<6);                    //green

// ================ RIGHT PORTS ================
#include <IOExpanderPort.h>
#include <RowPort_PCA9655E.h>
#include <ColPort_PCA9655E.h>

const uint8_t IOExpanderPort::ADDR = 0x18;

//row port
IOExpanderPort port1(1, 0);
RowPort_PCA9655E rowPort_R(port1);

//column and pin numbers on schematic_switch_matrix.png and schematic_pca9655_pin_assignments.png
//col port
IOExpanderPort port0(0, 0);
ColPort_PCA9655E colPort_R(port0, 1<<0 | 1<<1 );

//LED
LED_PCA9655E LED_R1(port1, 1<<5);               //blue

// =================== CODES ===================
Code_Sc s_a(KEY_A);
Code_Sc s_b(KEY_B);
Code_Sc s_c(KEY_C);
//Code_Sc s_d(KEY_D);
Code_Sc_LED s_d(KEY_D, LED_L1);

Code_Sc s_0(KEY_0);
Code_Sc s_1(KEY_1);
Code_Sc s_2(KEY_2);
//Code_Sc s_3(KEY_3);
Code_Sc_LED s_3(KEY_3, LED_R1);

// ================= LEFT ROWS =================
Key* const ptrsKeys_L0[] = { &s_a, &s_b };
Row_IOE row_L0(rowPort_L, 1<<0, colPort_L, ptrsKeys_L0); //strobe F0

Key* const ptrsKeys_L1[] = { &s_c,  &s_d };
Row_IOE row_L1(rowPort_L, 1<<1, colPort_L, ptrsKeys_L1); //strobe F1

// ================= RIGHT ROWS ================
Key* ptrsKeys_R0[] = { &s_0, &s_1 };
Row_IOE row_R0(rowPort_R, 1<<0, colPort_R, ptrsKeys_R0);

Key* ptrsKeys_R1[] = { &s_2, &s_3 };
Row_IOE row_R1(rowPort_R, 1<<1, colPort_R, ptrsKeys_R1);

// ################### MAIN ####################
void setup()
{
    Keyboard.begin();
    Wire.begin();

    delay(1000);        //time for OS to detect USB before printing
    Keyboard.print(F("activeState_AVR.ino "));
    debug.print_free_RAM();

    rowPort_R.begin();
    colPort_R.begin();
}

void loop()
{
    row_L0.process();
    row_L1.process();

    row_R0.process();
    row_R1.process();

//delay(500);
//Keyboard.println(F(""));
}
