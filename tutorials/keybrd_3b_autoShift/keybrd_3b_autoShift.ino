/* keybrd_3_autoShift_annotated.ino

This sketch:
    is a simple 2-layer keyboard with AutoShift
    runs on the first two rows and columns of a breadboard keyboard

| Layout | **0** | **1** |
|:------:|-------|-------|
|  **0** | shift | a  !  |
|  **1** | fn    | b  @  |

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
#include <Key_LayeredKeysArray.h>

//Matrix
#include <Row_uC.h>
#include <ScanDelay.h>

// ============ SPEED CONFIGURATION ============
ScanDelay scanDelay(9000);

// ================ ACTIVE STATE ===============
const bool Scanner_uC::STROBE_ON = LOW;
const bool Scanner_uC::STROBE_OFF = HIGH;

// =================== PINS ====================
uint8_t readPins[] = {14, 15};
uint8_t READ_PIN_COUNT = sizeof(readPins)/sizeof(*readPins);

// =================== CODES ===================
// ---------------- LAYER CODE -----------------
enum layers { NORMAL, FN };

LayerState layerState;
Code_LayerHold l_fn(FN, layerState);

/* ---------------- SCAN CODES -----------------
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
When a shift key is pressed, a standard keyboard driver will temporarily modify the normal action of another key when pressed together.
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
Key* const ptrsCodes_01[] = { &s_a, &s_exclamation };
Key_LayeredKeysArray k_01(ptrsCodes_01);

Key* const ptrsCodes_11[] = { &s_b, &s_at };
Key_LayeredKeysArray k_11(ptrsCodes_11);

LayerStateInterface& Key_LayeredKeysArray::refLayerState = layerState;

// =================== ROWS ====================
Key* const ptrsKeys_0[] = { &s_shift, &k_01 };
Row_uC row_0(0, readPins, READ_PIN_COUNT, ptrsKeys_0);

Key* const ptrsKeys_1[] = { &l_fn,  &k_11 };
Row_uC row_1(1, readPins, READ_PIN_COUNT, ptrsKeys_1);

// ################### MAIN ####################
void setup()
{
    Keyboard.begin();
}

void loop()
{
    row_0.process();
    row_1.process();
    scanDelay.delay();
}
