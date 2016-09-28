/* keybrd_5b_LED_on_IOE.ino

This sketch:
    is a simple 1-layer keyboard with CapsLck indicator LED on I/O expander
    runs on a two-matrix breadboard keyboard
    modified keybrd_4c_split_keyboard_with_IOE.ino by adding LED_capsLck

This layout table shows left and right matrices:

  Controller                I/O expander
| Left  | **0** | **1** | | Right | **0** | **1** |
|:-----:|-------|-------|-|:-----:|-------|-------|
| **1** |CapsLck| a  1  | | **1** | b  2  | c  3  |
| **0** |  fn   | x  =  | | **0** | y  -  | z  /  |
*/
// ################## GLOBAL ###################
// ================= INCLUDES ==================
#include <ScanDelay.h>
#include <LayerState_LED.h>
#include <Code_LayerHold.h>
#include <Code_LEDLock.h>
#include <Key_LayeredKeys.h>
#include <Code_Sc.h>
#include <Row.h>

//left matrix
#include <Scanner_uC.h>
#include <LED_uC.h>

//right matrix
#include <Port_MCP23S17.h>
#include <Scanner_IOE.h>
#include <LED_Port.h>

// ============ SPEED CONFIGURATION ============
ScanDelay scanDelay(9000);

// ==================== IC =====================
// ---------------- LEFT SCANNER ---------------
uint8_t readPins[] = {14, 15};
const uint8_t readPinCount = sizeof(readPins)/sizeof(*readPins);

Scanner_uC scanner_L(LOW, readPins, readPinCount);

// ----------------- LEFT LEDs -----------------
LED_uC LED_capsLck(21);

// --------------- RIGHT SCANNER ---------------
const uint8_t IOE_ADDR = 0x20;                  //MCP23S17 address, all 3 ADDR pins are grounded
Port_MCP23S17 portA(IOE_ADDR, 0, 1<<0 | 1<<1 ); //for read and LED
Port_MCP23S17 portB(IOE_ADDR, 1, 0);            //for strobe and LED

Scanner_IOE scanner_R(LOW, portB, portA);

/* ---------------- RIGHT LEDs -----------------
The LED_Port constructor parameters are a port and pin number that is connected to an LED.
*/
LED_Port LED_normal(portA, 1<<5);
LED_Port LED_fn(portB, 1<<4);

// =================== CODES ===================
// ---------------- LAYER CODE -----------------
enum layerIds { NORMAL, FN };

LEDInterface* prtsLayerLEDs[] = { &LED_normal, &LED_fn }; //array index matches enum layerIds
LayerState_LED layerState(prtsLayerLEDs);

Code_LayerHold l_fn(FN, layerState);

// ---------------- SCAN CODES -----------------
Code_Sc s_a(KEY_A);
Code_Sc s_b(KEY_B);
Code_Sc s_c(KEY_C);

Code_Sc s_x(KEY_X);
Code_Sc s_y(KEY_Y);
Code_Sc s_z(KEY_Z);

Code_Sc s_1(KEY_1);
Code_Sc s_2(KEY_2);
Code_Sc s_3(KEY_3);

Code_Sc s_minus(KEY_MINUS);
Code_Sc s_equal(KEY_EQUAL);
Code_Sc s_slash(KEY_SLASH);

Code_LEDLock o_capsLock(KEY_CAPS_LOCK, LED_capsLck);

// =================== KEYS ====================
//row0
Key* const ptrsKeys_01[] = { &s_a, &s_1 };
Key_LayeredKeys k_01(ptrsKeys_01);

Key* const ptrsKeys_02[] = { &s_b, &s_2 };
Key_LayeredKeys k_02(ptrsKeys_02);

Key* const ptrsKeys_03[] = { &s_c, &s_3 };
Key_LayeredKeys k_03(ptrsKeys_03);

//row1
Key* const ptrsKeys_11[] = { &s_x, &s_equal };
Key_LayeredKeys k_11(ptrsKeys_11);

Key* const ptrsKeys_12[] = { &s_y, &s_minus };
Key_LayeredKeys k_12(ptrsKeys_12);

Key* const ptrsKeys_13[] = { &s_z, &s_slash };
Key_LayeredKeys k_13(ptrsKeys_13);

LayerStateInterface& Key_LayeredKeys::refLayerState = layerState;

// =================== ROWS ====================
// ---------------- LEFT ROWS ------------------
Key* ptrsKeys_L0[] = { &o_capsLock, &k_01 };
const uint8_t KEY_COUNT_L0 = sizeof(ptrsKeys_L0)/sizeof(*ptrsKeys_L0);
Row row_L0(scanner_L, 0, ptrsKeys_L0, KEY_COUNT_L0);

Key* ptrsKeys_L1[] = { &l_fn, &k_11 };
const uint8_t KEY_COUNT_L1 = sizeof(ptrsKeys_L1)/sizeof(*ptrsKeys_L1);
Row row_L1(scanner_L, 1, ptrsKeys_L1, KEY_COUNT_L1);

// ---------------- RIGHT ROWS -----------------
Key* ptrsKeys_R0[] = { &k_02, &k_03};
const uint8_t KEY_COUNT_R0 = sizeof(ptrsKeys_R0)/sizeof(*ptrsKeys_R0);
Row row_R0(scanner_R, 1<<0, ptrsKeys_R0, KEY_COUNT_R0);

Key* ptrsKeys_R1[] = { &k_12,  &k_13 };
const uint8_t KEY_COUNT_R1 = sizeof(ptrsKeys_R1)/sizeof(*ptrsKeys_R1);
Row row_R1(scanner_R, 1<<1, ptrsKeys_R1, KEY_COUNT_R1);

/* ################### MAIN ####################
LayerState_LED::begin() is called after Scanner_IOE::begin()
so that scanner's ports can turn on LayerState_LED's default-layer LED.
*/
void setup()
{
    Keyboard.begin();
    scanner_R.begin();
    layerState.begin();                 //call LayerState_LED::begin() after Scanner_IOE::begin()
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
