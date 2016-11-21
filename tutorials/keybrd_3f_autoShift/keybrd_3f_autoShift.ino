/* keybrd_3f_autoShift.ino

This sketch:
    is a simple 2-layer keyboard with AutoShift
    runs on the first two rows and columns of a breadboard keyboard

| Layout | **0** | **1** |
|:------:|-------|-------|
|  **0** | a  !  | b  @  |
|  **1** |  fn   | shift |

The layered keys in row 0 have two layers; one character for each layer.
Letters 'a' and 'b' are on the normal layer.  Symbols '!' and '@' are one the fn layer.
Holding the fn key down makes it the active layer.  Releasing the fn key restores the normal layer.
*/
// ################## GLOBAL ###################
// ================= INCLUDES ==================

//Keys
#include <Code_Sc.h>
#include <Code_ScS.h>
#include <Code_Shift.h>
#include <LayerState.h>
#include <Code_LayerHold.h>
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
enum layerIds { NORMAL, FN };

LayerState layerState;
Code_LayerHold l_fn(FN, layerState);

/* ----------------- SCANCODES -----------------
The "Sc" in Code_Sc means "scancode".
When a Code_Sc is pressed, it sends its scancode.
*/
Code_Sc s_a(KEY_A);
Code_Sc s_b(KEY_B);

/* The "ScS" in Code_ScS means "scancode shifted".
When Code_ScS is pressed, it calls Code_AutoShift before sending its scancode.
*/
Code_ScS s_exclamation(KEY_1);
Code_ScS s_at(KEY_2);

// ----------------- SHIFT CODE ----------------
/*
The Code_Shift constructor takes one shift scancode.
*/
Code_Shift s_shift(MODIFIERKEY_LEFT_SHIFT);

/*
Code_Shift pointers are placed in an array because most keyboards have a left and right shift.
This sketch only has one shift code.
*/
Code_Shift* const ptrsS[] = { &s_shift };
Code_Shift* const* const Code_AutoShift::ptrsShifts = ptrsS;
const uint8_t Code_AutoShift::shiftCount = sizeof(ptrsS)/sizeof(*ptrsS);

/*
HOW SHIFT WORKS
When a shift key is pressed, a standard keyboard driver will temporarily modify the action of other scancodes.
    KEY_1 writes '1'
    MODIFIERKEY_LEFT_SHIFT + KEY_1 writes '!'

    KEY_2 writes '2'
    MODIFIERKEY_LEFT_SHIFT + KEY_2 writes '@'

HOW AUTOSHIFT WORKS
Code_ScS takes care of the MODIFIERKEY_LEFT_SHIFT automatically
When the user presses '!' or '@' on the fn layer:
    Code_AutoShift checks the position of each shift key
    Code_ScS sends MODIFIERKEY_LEFT_SHIFT scancode if needed
    Code_ScS sends its scancode
*/

// =================== KEYS ====================
Key* const ptrsKeys_00[] = { &s_a, &s_exclamation };
Key_LayeredKeys k_00(ptrsKeys_00);

Key* const ptrsKeys_01[] = { &s_b, &s_at };
Key_LayeredKeys k_01(ptrsKeys_01);

LayerStateInterface& Key_LayeredKeys::refLayerState = layerState;

// =================== ROWS ====================
Key* const ptrsKeys_0[] = { &k_00, &k_01 };
uint8_t keyCount_0 = sizeof(ptrsKeys_0)/sizeof(*ptrsKeys_0);
Row row_0(scanner, 0, ptrsKeys_0, keyCount_0);

Key* const ptrsKeys_1[] = { &l_fn, &s_shift };
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
