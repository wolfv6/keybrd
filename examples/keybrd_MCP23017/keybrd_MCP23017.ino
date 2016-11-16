/* keybrd_MCP23017.ino

This sketch:
    is a simple 1-layer keyboard
    runs on two matrices of a breadboard keyboard
    runs on both MCP23017 and MCP23018 IOEs (LED on/off will be reversed on MCP23017)

  Controller                I/O expander
| Left  | **0** | **1** | | Right | **0** | **1** |
|-------|-------|-------| |-------|-------|-------|
| **1** |   1   |   2   | | **1** |   3   |   4   |
| **0** |   a   |   b   | | **0** |  fn   | z   9 |

MCP23017 pin assignments
DESTINATION  PIN PIN_NUMBER  PIN   DESTINATION
     row0    GPB0  1     28 GPA7
     row1    GPB1  2     27 GPA6
             GPB2  3     26 GPA5
             GPB3  4     25 GPA4
             GPB4  5     24 GPA3
             GPB5  6     23 GPA2
             GPB6  7     22 GPA1    col1
             GPB7  8     21 GPA0    col0
     LC 3.3V VDD   9     20 INTA
     GND     VSS  10     19 INTB
              NC  11     18 /RESET   VDD
     LC 19   SCL  12     17 A2       GND
     LC 18   SDA  13     16 A1       GND
              NC  14     15 A0       GND

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

#include <Code_LayerHold.h>
#include <Key_LayeredKeys.h>
#include <LayerState_LED.h>
#include <LED_PortOpenDrain.h>

//left matrix
#include <Scanner_uC.h>

//right matrix
#include <Port_MCP23018.h>
#include <Scanner_IOE.h>

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
LED_PortOpenDrain LED_normal(portA, 1<<2);      //LED on/off will be reversed on MCP23017 
LED_PortOpenDrain LED_fn(portB, 1<<2);          // because it's not open drain

// =================== CODES ===================
// ---------------- LAYER CODES ----------------
enum layerIds { NORMAL, FN };

LEDInterface* prtsLayerLEDs[] = { &LED_normal, &LED_fn }; //array index matches enum layerIds
LayerState_LED layerState(prtsLayerLEDs);

Code_LayerHold l_fn(FN, layerState);

// ---------------- SCAN CODES -----------------
Code_Sc s_a(KEY_A);
Code_Sc s_b(KEY_B);
Code_Sc s_z(KEY_Z);

Code_Sc s_1(KEY_1);
Code_Sc s_2(KEY_2);
Code_Sc s_3(KEY_3);
Code_Sc s_4(KEY_4);
Code_Sc s_9(KEY_9);

// =================== KEYS ====================
Key* const ptrsKeys_z9[] = { &s_z, &s_9 };
Key_LayeredKeys k_z9(ptrsKeys_z9);

LayerStateInterface& Key_LayeredKeys::refLayerState = layerState;

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

Key* ptrsKeys_R1[] = { &l_fn,  &k_z9 };
const uint8_t KEY_COUNT_R1 = sizeof(ptrsKeys_R1)/sizeof(*ptrsKeys_R1);
Row row_R1(scanner_R, 1<<1, ptrsKeys_R1, KEY_COUNT_R1);

// ################### MAIN ####################
void setup()
{
    delay(6000);
    Keyboard.print("keybrd_MCP23017.ino ");

    scanner_R.begin();
    layerState.begin();
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
