/* keybrd_PCA9655E.ino

  Teensy 2.0 controller     PCA9655E I/O expander
| Left  | **0** | **1** | | Right | **0** | **1** |
|:-----:|-------|-------| |:-----:|-------|-------|
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
#include <PortWrite_PCA9655E.h>
#include <PortRead_PCA9655E.h>
#include <Scanner_IOE.h>

// ============ SPEED CONFIGURATION ============
ScanDelay scanDelay(9000);

// ================ LEFT SCANNER ===============
uint8_t readPins_L[] = {0, 1};
uint8_t readPinCount_L = sizeof(readPins_L)/sizeof(*readPins_L);

Scanner_uC scanner_L(HIGH, readPins_L, readPinCount_L);

// =============== RIGHT SCANNER ===============
const uint8_t PortIOE::DEVICE_ADDR = 0x18;

PortIOE port_R1(1, 0);
PortWrite_PCA9655E portWrite_R1(port_R1);

PortIOE port_R0(0, 0);
//PortWrite_PCA9655E portWrite_R0(port_R0);     //for LEDs
PortRead_PCA9655E portRead_R0(port_R0, 1<<0 | 1<<1 );

Scanner_IOE scanner_R(HIGH, portWrite_R1, portRead_R0);

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
uint8_t KEY_COUNT_L0 = sizeof(ptrsKeys_L0)/sizeof(*ptrsKeys_L0);
Row row_L0(scanner_L, 21, ptrsKeys_L0, KEY_COUNT_L0);

Key* ptrsKeys_L1[] = { &s_a, &s_b };
uint8_t KEY_COUNT_L1 = sizeof(ptrsKeys_L1)/sizeof(*ptrsKeys_L1);
Row row_L1(scanner_L, 20, ptrsKeys_L1, KEY_COUNT_L1);

// ---------------- RIGHT ROWS -----------------
Key* ptrsKeys_R0[] = { &s_3,  &s_4 };
uint8_t KEY_COUNT_R0 = sizeof(ptrsKeys_R0)/sizeof(*ptrsKeys_R0);
Row row_R0(scanner_R, 1<<0, ptrsKeys_R0, KEY_COUNT_R0);

Key* ptrsKeys_R1[] = { &s_c,  &s_d };
uint8_t KEY_COUNT_R1 = sizeof(ptrsKeys_R1)/sizeof(*ptrsKeys_R1);
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
