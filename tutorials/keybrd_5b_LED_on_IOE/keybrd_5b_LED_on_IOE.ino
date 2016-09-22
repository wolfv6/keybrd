/* keybrd_5b_LED_on_IOE.ino

This sketch:
    is a simple 1-layer keyboard with CapsLck indicator LED on I/O expander
    runs on two matrices of a breadboard keyboard
    modified keybrd_4c_split_keyboard_with_IOE.ino by adding LED_CapsLck

This layout table shows left and right matrices:

| Left  | **0** | **1** | | Right | **0** | **1** |
|:-----:|-------|-------|-|:-----:|-------|-------|
| **1** |   1   |   2   | | **1** |   3   |CapsLck|
| **0** |   a   |   b   | | **0** |   c   |   d   |
*/
// ################## GLOBAL ###################
// ================= INCLUDES ==================
#include <ScanDelay.h>
#include <Code_LEDLock.h>
#include <Code_Sc.h>
#include <Row.h>

//left matrix
#include <Scanner_uC.h>

//right matrix
#include <PortIOE.h>
#include <PortWrite_MCP23S17.h>
#include <PortRead_MCP23S17.h>
#include <Scanner_IOE.h>
#include <LED_IOE.h>

// ============ SPEED CONFIGURATION ============
ScanDelay scanDelay(9000);

// ================ LEFT SCANNER ===============
uint8_t readPins[] = {14, 15};
const uint8_t READPIN_COUNT = sizeof(readPins)/sizeof(*readPins);

Scanner_uC scanner_L(LOW, readPins, READPIN_COUNT);

// =============== RIGHT SCANNER ===============
const uint8_t PortIOE::DEVICE_ADDR = 0x20;      //MCP23S17 address with all 3 ADDR pins are grounded

PortIOE port_A(0);
PortRead_MCP23S17 portRead(port_A, 1<<0 | 1<<1 );
PortWrite_MCP23S17 portWriteA(port_A); //for LED
//todo portWriteA(port_A) instantiation would not be needed if PortRead_MCP23S17 had write()
//  consider moving PortWrite_MCP23S17::write to Port_MCP23S17 (parent)
//  and passing portRead to LED_IOE
//  same for PCA9655E

PortIOE port_B(1);
PortWrite_MCP23S17 portWrite(port_B);

Scanner_IOE scanner_R(LOW, portWrite, portRead);

// ================ RIGHT LEDs =================
LED_IOE LED_CapsLck(portWriteA, 1<<6); //tested LED on port A (read)
//LED_IOE LED_CapsLck(portWrite, 1<<6);//tested LED on port B (write)

// =================== CODES ===================
Code_Sc s_a(KEY_A);
Code_Sc s_b(KEY_B);
Code_Sc s_c(KEY_C);
Code_Sc s_d(KEY_D);

Code_Sc s_1(KEY_1);
Code_Sc s_2(KEY_2);
Code_Sc s_3(KEY_3);

Code_LEDLock o_capsLock(KEY_CAPS_LOCK, LED_CapsLck);

// =================== ROWS ====================
// ---------------- LEFT ROWS ------------------
Key* ptrsKeys_L0[] = { &s_1, &s_2 };
const uint8_t KEY_COUNT_L0 = sizeof(ptrsKeys_L0)/sizeof(*ptrsKeys_L0);
Row row_L0(scanner_L, 0, ptrsKeys_L0, KEY_COUNT_L0);

Key* ptrsKeys_L1[] = { &s_a, &s_b };
const uint8_t KEY_COUNT_L1 = sizeof(ptrsKeys_L1)/sizeof(*ptrsKeys_L1);
Row row_L1(scanner_L, 1, ptrsKeys_L1, KEY_COUNT_L1);

// ---------------- RIGHT ROWS -----------------
Key* ptrsKeys_R0[] = { &s_3, &o_capsLock };
const uint8_t KEY_COUNT_R0 = sizeof(ptrsKeys_R0)/sizeof(*ptrsKeys_R0);
Row row_R0(scanner_R, 1<<0, ptrsKeys_R0, KEY_COUNT_R0);

Key* ptrsKeys_R1[] = { &s_c,  &s_d };
const uint8_t KEY_COUNT_R1 = sizeof(ptrsKeys_R1)/sizeof(*ptrsKeys_R1);
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
