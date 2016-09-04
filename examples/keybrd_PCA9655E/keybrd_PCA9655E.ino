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

//left matrix
#include <Row_uC.h>

//right matrix
#include <Row_IOE.h>
#include <PortIOE.h>
#include <PortWrite_PCA9655E.h>
#include <PortRead_PCA9655E.h>

// ============ SPEED CONFIGURATION ============
ScanDelay scanDelay(9000);

// =============== LEFT uC MATRIX ==============
const bool Scanner_uC::STROBE_ON = HIGH;       //active high
const bool Scanner_uC::STROBE_OFF = LOW;

uint8_t readPins_L[] = {0, 1};

// ============== RIGHT IOE MATRIX =============
const bool Scanner_Port::STROBE_ON = HIGH;      //active high
const bool Scanner_Port::STROBE_OFF = LOW;

const uint8_t PortIOE::DEVICE_ADDR = 0x18;

// ------------------ PORT 1 -------------------
PortIOE port1_R(1, 0);
PortWrite_PCA9655E portWrite1_R(port1_R);

// ------------------ PORT 0 -------------------
PortIOE port0_R(0, 0);
PortWrite_PCA9655E portWrite0_R(port0_R);
PortRead_PCA9655E portRead0_R(port0_R, 1<<0 | 1<<1 );

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
Row_uC row_L0(21, readPins_L, KEY_COUNT_L0, ptrsKeys_L0);

Key* ptrsKeys_L1[] = { &s_a, &s_b };
uint8_t KEY_COUNT_L1 = sizeof(ptrsKeys_L1)/sizeof(*ptrsKeys_L1);
Row_uC row_L1(20, readPins_L, KEY_COUNT_L1, ptrsKeys_L1);

// ---------------- RIGHT ROWS -----------------
Key* ptrsKeys_R0[] = { &s_3,  &s_4 };
uint8_t KEY_COUNT_R0 = sizeof(ptrsKeys_R0)/sizeof(*ptrsKeys_R0);
Row_IOE row_R0(portWrite1_R, 1<<0, portRead0_R, KEY_COUNT_R0, ptrsKeys_R0);

Key* ptrsKeys_R1[] = { &s_c,  &s_d };
uint8_t KEY_COUNT_R1 = sizeof(ptrsKeys_R1)/sizeof(*ptrsKeys_R1);
Row_IOE row_R1(portWrite1_R, 1<<1, portRead0_R, KEY_COUNT_R1, ptrsKeys_R1);

// ################### MAIN ####################
void setup()
{
    Keyboard.begin();
    Wire.begin();                               //Wire.begin() must be called before port begin()
    portWrite1_R.begin();
    portRead0_R.begin();
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
