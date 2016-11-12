/* keybrd_PCA9655E.ino
keyboard layout is same as top-left keys of DH matrices:

  Controller                I/O expander
| Left  | **0** | **1** | | Right | **2** | **3** |
|:-----:|-------|-------| |:-----:|-------|-------|
| **1** |   q   |   w   | | **1** |   u   |   i   |
| **0** |   [   |   b   | | **0** |   h   |   y   |

PCA9655E pin assignments are compatible with this sketch and keybrd_DH.ino
DESTINATION  PIN PIN_NUMBER  PIN   DESTINATION
       x     INT  1      24  VDD   Teensy LC 3.3V
      SCL    AD1  2      23  SDA   Teensy LC 18
      GND    AD2  3      22  SCL   Teensy LC 19
      GND  IO0_0  4      21  AD0   SCL
      GND  IO0_1  5      20  IO1_6  x
      col2 IO0_2  6      19  IO1_5  x
      col3 IO0_3  7      18  IO1_4  x
      GND  IO0_4  8      17  IO1_4  x
      GND  IO0_5  9      16  IO1_3  x
       x   IO0_6 10      15  IO1_2  x
       x   IO0_7 11      14  IO1_1 row1
      GND    VSS 12      13  IO1_0 row2
*/
// ################## GLOBAL ###################
// ================= INCLUDES ==================
#include <ScanDelay.h>
#include <Code_Sc.h>
#include <Row.h>

//left matrix
#include <Scanner_uC.h>

//right matrix
#include <Port_PCA9655E.h>
#include <Scanner_IOE.h>

// ============ SPEED CONFIGURATION ============
ScanDelay scanDelay(9000);

// ================ LEFT SCANNER ===============
uint8_t readPins[] = {0, 1};
uint8_t readPinCount = sizeof(readPins)/sizeof(*readPins);

Scanner_uC scanner_L(HIGH, readPins, readPinCount);

// =============== RIGHT SCANNER ===============
const uint8_t IOE_ADDR = 0x18;                  //AD2=GND AD1=SCL AD0=SCL

Port_PCA9655E port0(IOE_ADDR, 0, 1<<0 | 1<<1 | 1<<2 | 1<<3 | 1<<4 | 1<<5 ); //for read
Port_PCA9655E port1(IOE_ADDR, 1, 0);            //for strobe

Scanner_IOE scanner_R(HIGH, port1, port0);

// =================== CODES ===================
Code_Sc s_B(KEY_B);
Code_Sc s_I(KEY_I);
Code_Sc s_H(KEY_H);
Code_Sc s_Q(KEY_Q);
Code_Sc s_W(KEY_W);
Code_Sc s_U(KEY_U);
Code_Sc s_Y(KEY_Y);

Code_Sc s_0(KEY_0);
Code_Sc s_1(KEY_1);
Code_Sc s_leftBracket(KEY_LEFT_BRACE);

// =================== ROWS ====================
// ---------------- LEFT ROWS ------------------
Key* ptrsKeys_L0[] = { &s_Q, &s_W };
uint8_t KEY_COUNT_L0 = sizeof(ptrsKeys_L0)/sizeof(*ptrsKeys_L0);
Row row_L0(scanner_L, 21, ptrsKeys_L0, KEY_COUNT_L0);

Key* ptrsKeys_L1[] = { &s_leftBracket, &s_B };
uint8_t KEY_COUNT_L1 = sizeof(ptrsKeys_L1)/sizeof(*ptrsKeys_L1);
Row row_L1(scanner_L, 20, ptrsKeys_L1, KEY_COUNT_L1);

// ---------------- RIGHT ROWS -----------------
Key* ptrsKeys_R0[] = { &s_0, &s_1, &s_U,  &s_I };
uint8_t KEY_COUNT_R0 = sizeof(ptrsKeys_R0)/sizeof(*ptrsKeys_R0);
Row row_R0(scanner_R, 1<<0, ptrsKeys_R0, KEY_COUNT_R0);

Key* ptrsKeys_R1[] = { &s_0, &s_1, &s_H,  &s_Y };
uint8_t KEY_COUNT_R1 = sizeof(ptrsKeys_R1)/sizeof(*ptrsKeys_R1);
Row row_R1(scanner_R, 1<<1, ptrsKeys_R1, KEY_COUNT_R1);

/*
*/
// ################### MAIN ####################
void setup()
{
    delay(6000);
    Keyboard.print("keybrd_PCA9655E.ino ");

    //Keyboard.begin(); not needed ?? it's in DH mainSketch.cpp and keybrd_4c_split_keyboard_with_IOE.ino
    scanner_R.begin();
}

void loop()
{
    //left matrix (commented because keys are not connected)
    //row_L0.process();
    //row_L1.process();

    //right matrix
    row_R0.process();
    row_R1.process();

    scanDelay.delay();
    //debug.printScansPerSecond();
    //debug.printMicrosecondsPerScan();
}
