/* keybrd_3g_shift_pairings.ino

This sketch:
    is a simple 2-layer keyboard with AutoShift
    runs on the first two rows and columns of a breadboard keyboard

| Layout | **0** | **1** |
|:------:|-------|-------|
|  **0** |  8 (  |  = -  |
|  **1** | shift |  5 %  |

The layout has one shift key in the lower right.  The top-row keys are custom pairings.
Characters '8' and '=' are on the normal layer.  Characters '(' and '-' are on the shift layer.
Holding the shift key down makes it the active layer.
Releasing the shift key restores the normal layer.
*/
// ################## GLOBAL ###################
// ================= INCLUDES ==================

//Keys
#include <Code_Sc.h>
#include <Code_ScNS.h>
#include <Code_Shift.h>
#include <LayerState.h>
#include <Code_LayerHoldShift.h>
#include <Key_LayeredKeys.h>

//Matrix
#include <Row.h>
#include <Scanner_uC.h>
#include <ScanDelay.h>

// ============ SPEED CONFIGURATION ============
ScanDelay scanDelay(9000);

// ================== SCANNER ==================
uint8_t readPins[] = {14, 15};
uint8_t readPinCount = sizeof(readPins)/sizeof(*readPins);

Scanner_uC scanner(LOW, readPins, readPinCount);

// =================== CODES ===================
// ---------------- LAYER CODE -----------------
enum layerIds { NORMAL, SHIFT };
LayerState layerState;
Code_Shift s_shift(MODIFIERKEY_LEFT_SHIFT);
Code_LayerHoldShift l_shift(SHIFT, layerState, s_shift);

/* ----------------- SCANCODES -----------------
The "Sc" in Code_Sc means "scancode".
When a Code_Sc is pressed, it sends its scancode.
*/
Code_Sc s_a(KEY_A);
Code_Sc s_5(KEY_5);
Code_Sc s_8(KEY_8);
Code_Sc s_equal(KEY_EQUAL);
Code_Sc s_leftParen(KEY_9);

/* The "ScNS" in Code_ScNS means "scancode not shifted".
When Code_ScNS is pressed, it calls Code_AutoShift before sending its scancode.
*/
Code_ScNS ns_minus(KEY_MINUS);

/*
Code_Shift pointers are placed in an array because most keyboards have a left and right shift.
This sketch only has one shift code.
*/
Code_Shift* const ptrsS[] = { &s_shift };
Code_Shift* const* const Code_AutoShift::ptrsShifts = ptrsS;
const uint8_t Code_AutoShift::shiftCount = sizeof(ptrsS)/sizeof(*ptrsS);

// =============== LAYERED KEYS ================
Key* const ptrsKeys_00[] = { &s_8, &s_leftParen }; //custom key pairing
Key_LayeredKeys k_00(ptrsKeys_00);

Key* const ptrsKeys_01[] = { &s_equal, &ns_minus }; //custom key pairing
Key_LayeredKeys k_01(ptrsKeys_01);

LayerStateInterface& Key_LayeredKeys::refLayerState = layerState;

// =================== ROWS ====================
Key* const ptrsKeys_0[] = { &k_00, &k_01 };
uint8_t keyCount_0 = sizeof(ptrsKeys_0)/sizeof(*ptrsKeys_0);
Row row_0(scanner, 0, ptrsKeys_0, keyCount_0);

Key* const ptrsKeys_1[] = { &l_shift, &s_5 };
uint8_t keyCount_1 = sizeof(ptrsKeys_1)/sizeof(*ptrsKeys_1);
Row row_1(scanner, 1, ptrsKeys_1, keyCount_1);

// ################### MAIN ####################
void setup()
{
}

void loop()
{
    row_0.process();
    row_1.process();
    scanDelay.delay();
}
