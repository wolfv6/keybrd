/* keybrd_MCP23018.ino

This sketch:
    is a simple 1-layer keyboard
    runs on two matrices of a breadboard keyboard

  Controller                I/O expander
| Left  | **0** | **1** | | Right | **0** | **1** |
|-------|-------|-------| |-------|-------|-------|
| **1** |   1   |   2   | | **1** |   3   |   4   |
| **0** |   a   |   b   | | **0** |   c   |   d   |

MCP23018 pin assignments
DESTINATION  PIN PIN_NUMBER  PIN    DESTINATION
     GND     VSS   1     28  NC
             NC    2     27  GPA7
     row0    GPB0  3     26  GPA6
     row1    GPB1  4     25  GPA5
             GPB2  5     24  GPA4
             GPB4  7     22  GPA2
             GPB5  8     21  GPA1   col1
             GPB6  9     20  GPA0   col0
             GPB7 10     19  INTA
     LC 3.3V VCC  11     18  INTB
     LC 19   SCL  12     17  NC
     LC 18   SDA  13     16  /RESET VCC
             NC   14     15  ADDR   GND

*/
// ################## GLOBAL ###################
// ================= INCLUDES ==================
#include <ScanDelay.h>
#include <Code_Sc.h>
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

// =============== RIGHT SCANNER ===============
const uint8_t IOE_ADDR = 0x20;                  //MCP23018 ADDR pin grounded

Port_MCP23018 portA(IOE_ADDR, 0, 1<<0 | 1<<1 ); //read pins 0, 1
Port_MCP23018 portB(IOE_ADDR, 1, 0);
Scanner_IOE scanner_R(LOW, portB, portA);

// ================= RIGHT LED =================
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

// =================== ROWS ====================
// ---------------- LEFT ROWS ------------------
Key* ptrsKeys_L0[] = { &s_1, &s_2 };
const uint8_t KEY_COUNT_L0 = sizeof(ptrsKeys_L0)/sizeof(*ptrsKeys_L0);
Row row_L0(scanner_L, 0, ptrsKeys_L0, KEY_COUNT_L0);

Key* ptrsKeys_L1[] = { &s_a, &s_b };
const uint8_t KEY_COUNT_L1 = sizeof(ptrsKeys_L1)/sizeof(*ptrsKeys_L1);
Row row_L1(scanner_L, 1, ptrsKeys_L1, KEY_COUNT_L1);

// ---------------- RIGHT ROWS -----------------
Key* ptrsKeys_R0[] = { &s_3, &s_4 };
const uint8_t KEY_COUNT_R0 = sizeof(ptrsKeys_R0)/sizeof(*ptrsKeys_R0);
Row row_R0(scanner_R, 1<<0, ptrsKeys_R0, KEY_COUNT_R0);

Key* ptrsKeys_R1[] = { &s_c,  &s_d };
const uint8_t KEY_COUNT_R1 = sizeof(ptrsKeys_R1)/sizeof(*ptrsKeys_R1);
Row row_R1(scanner_R, 1<<1, ptrsKeys_R1, KEY_COUNT_R1);

// ################### MAIN ####################
void setup()
{
    delay(6000);
    Keyboard.print("keybrd_MCP23018.ino ");

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
