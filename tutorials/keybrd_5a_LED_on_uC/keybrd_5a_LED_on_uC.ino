/* keybrd_5a_LED_on_uC.ino

This sketch:
    is firmware for a simple 2-layer keyboard with three LEDs
    runs on the first two rows and columns of a breadboard keyboard

| Layout | **0** | **1** |
|:------:|-------|-------|
|  **0** |CapsLck| a  1  |
|  **1** |  fn   | x  =  |
*/

// ################## GLOBAL ###################
// ================= INCLUDES ==================
//Keys
#include <Code_Sc.h>
#include <Code_LEDLock.h>
#include <LayerState_LED.h>
#include <Code_LayerHold.h>
#include <Key_LayeredKeys.h>

#include <Row.h>
#include <Scanner_uC.h>
#include <ScanDelay.h>
#include <LED_uC.h>

// ============ SPEED CONFIGURATION ============
ScanDelay scanDelay(9000);

// ================== SCANNER ==================
uint8_t readPins[] = {14, 15};
uint8_t readPinCount = sizeof(readPins)/sizeof(*readPins);

Scanner_uC scanner(LOW, readPins, readPinCount);

/* ==================== LEDs ===================
The LED_uC constructor parameter is for an Aduino pin number that is connected to an LED.
In this example, the LED_uC objects are named after the states they indicate.
*/
LED_uC LED_normal(16);
LED_uC LED_fn(17);
LED_uC LED_capsLck(21);

// =================== CODES ===================
/* ---------------- LAYER CODE -----------------
LayerState_LED is similar to LayerState introduced in keybrd_3a_multi-layerHold.ino, but with LEDs.
The LayerState_LED turns on the LED of the active layer.
The prtsLayerLEDs[] array contains one LED per layer.
The active layerId is used as an index to dereference the prtsLayerLEDs[] array.
*/
enum layerIds { NORMAL, FN };

LEDInterface* prtsLayerLEDs[] = { &LED_normal, &LED_fn }; //enum layerIds align with array index
LayerState_LED layerState(prtsLayerLEDs);

Code_LayerHold l_fn(FN, layerState);

/* ---------------- SCAN CODES -----------------
When a Code_LEDLock object is pressed, it sends its scancode and updates the its LED.
Scancodes can be one of: KEY_CAPS_LOCK, KEY_SCROLL_LOCK, or KEY_NUM_LOCK.
For example, when o_capsLock is pressed, it sends KEY_CAPS_LOCK scancode and updates LED_capsLck.
*/
Code_LEDLock o_capsLock(KEY_CAPS_LOCK, LED_capsLck);

Code_Sc s_a(KEY_A);
Code_Sc s_x(KEY_X);

Code_Sc s_1(KEY_1);
Code_Sc s_equal(KEY_EQUAL);

// =================== KEYS ====================
Key* const ptrsKeys_01[] = { &s_a, &s_1 };
Key_LayeredKeys k_01(ptrsKeys_01);

Key* const ptrsKeys_11[] = { &s_x, &s_equal };
Key_LayeredKeys k_11(ptrsKeys_11);

LayerStateInterface& Key_LayeredKeys::refLayerState = layerState;

// =================== ROWS ====================
Key* const ptrsKeys_0[] = { &o_capsLock, &k_01 };
uint8_t keyCount_0 = sizeof(ptrsKeys_0)/sizeof(*ptrsKeys_0);
Row row_0(scanner, 0, ptrsKeys_0, keyCount_0);

Key* const ptrsKeys_1[] = { &l_fn, &k_11 };
uint8_t keyCount_1 = sizeof(ptrsKeys_1)/sizeof(*ptrsKeys_1);
Row row_1(scanner, 1, ptrsKeys_1, keyCount_1);

/* ################### MAIN ####################
layerState.begin() turns on the LED of the default layer.
*/
void setup()
{
    layerState.begin();
}

void loop()
{
    row_0.process();
    row_1.process();
    scanDelay.delay();
}
