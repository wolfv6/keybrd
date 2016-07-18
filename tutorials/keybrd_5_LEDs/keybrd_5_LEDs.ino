/* keybrd_5_LEDs.ino

This sketch:
    is firmware for a simple 2-layer keyboard with three LEDs
    runs on the first two rows and columns of a breadboard keyboard

| Layout | **0** | **1** |
|:------:|-------|-------|
|  **0** |CapsLck| a  1  |
|  **1** |  fn   | b  2  |
*/

// ################## GLOBAL ###################
// ================= INCLUDES ==================
//Keys
#include <Code_Sc.h>
#include <Code_LEDLock.h>
#include <LayerState_LED.h>
#include <Code_LayerHold.h>
#include <Key_LayeredKeysArray.h>

#include <Row_uC.h>
#include <ScanDelay.h>
#include <LED_uC.h>

// ============ SPEED CONFIGURATION ============
ScanDelay scanDelay(9000);

// ================ ACTIVE STATE ===============
const bool Scanner_uC::STROBE_ON = LOW;
const bool Scanner_uC::STROBE_OFF = HIGH;

// ================= PINS =================
uint8_t readPins[] = {14, 15};
uint8_t READ_PIN_COUNT = sizeof(readPins)/sizeof(*readPins);

/* ==================== LEDs ===================
The LED_uC constructor parameter is for an Aduino pin that is connected to an LED.
LED_uC objects are passed to other objects that want to turn the LED on or off.
In this example, the LED_uC objects are named after the states they indicate.

The prtsLayerLEDs[] array contains one LED per layer, it is used to indicate the current layer.
*/
LED_uC LED_normal(16);
LED_uC LED_fn(17);
LED_uC LED_CapsLck(21);

LED* prtsLayerLEDs[] = { &LED_normal, &LED_fn };

// =================== CODES ===================
/* ---------------- LAYER CODE -----------------
LayerState_LED is similar to LayerState, introduced in keybrd_3a_multi-layer.ino, but with LEDs.
The LayerState_LED turns on the LED of the current layer.
The active layer is used as an index to dereference the prtsLayerLEDs[] array.
*/
enum layers { NORMAL, FN };

LayerState_LED layerState(prtsLayerLEDs);

Code_LayerHold l_fn(FN, layerState);

/* ---------------- SCAN CODES -----------------
When a Code_LEDLock object is pressed, it sends a scancodes and updates the its LED.
Scancodes can be one of KEY_CAPS_LOCK, KEY_SCROLL_LOCK, or KEY_NUM_LOCK.
For example, when o_capsLock is pressed, it sends KEY_CAPS_LOCK scancode and updates LED_CapsLck.
*/
Code_LEDLock o_capsLock(KEY_CAPS_LOCK, LED_CapsLck);

Code_Sc s_a(KEY_A);
Code_Sc s_b(KEY_B);
Code_Sc s_1(KEY_1);
Code_Sc s_2(KEY_2);

// =================== KEYS ====================
Key* const ptrsCodes_01[] = { &s_a, &s_1 };
Key_LayeredKeysArray k_01(ptrsCodes_01);

Key* const ptrsCodes_11[] = { &s_b, &s_2 };
Key_LayeredKeysArray k_11(ptrsCodes_11);

LayerStateInterface& Key_LayeredKeysArray::refLayerState = layerState;

// =================== ROWS ====================
Key* const ptrsKeys_0[] = { &o_capsLock, &k_01 };
Row_uC row_0(0, readPins, READ_PIN_COUNT, ptrsKeys_0);

Key* const ptrsKeys_1[] = { &l_fn, &k_11 };
Row_uC row_1(1, readPins, READ_PIN_COUNT, ptrsKeys_1);

/* ################### MAIN ####################
layerState.begin() turns on the LED of the initial active layer.
*/
void setup()
{
    Keyboard.begin();
    layerState.begin();
}

void loop()
{
    row_0.process();
    row_1.process();
    scanDelay.delay();
}
