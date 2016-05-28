/* keybrd_3_autoShift_annotated.ino

This sketch:
    is a simple 2-layer keyboard with AutoShift
    runs on the first two rows and columns of a breadboard keyboard
    is annotated with a walk-through narrative

This layout table shows how keys are arranged on the keyboard:

| Layout | **0** | **1** |
|:------:|-------|-------|
|  **0** | a  !  | b  @  |
|  **1** | fn    | shift |

The layered keys in row 0 have two layers; one character for each layer.
Letters 'a' and 'b' are on the normal layer.  Symbols '!' and '@' are one the fn layer.
Holding the fn key down makes it the active layer.  Releasing the fn key restores the normal layer.
*/
// ################## GLOBAL ###################
// ================= INCLUDES ==================
//Ports
#include <RowPort_AVR_Optic.h>
#include <ColPort_AVR.h>

//Codes
#include <Code_Sc.h>
#include <Code_ScS.h>
#include <Code_Shift.h>
#include <LayerState.h>
#include <Code_LayerHold.h>
#include <Key_LayeredKeysArray.h>

//Matrix
#include <Row.h>
#include <Matrix.h>

// ============ SPEED CONFIGURATIONS ============
const unsigned int Row::DELAY_MICROSECONDS = 1000;

// =================== PORTS ===================
RowPort_AVR_Optic rowPortF(DDRF, PORTF);

ColPort_AVR colPortB(DDRB, PORTB, PINB, 1<<0 | 1<<1 );

ColPort* const ptrsColPorts[] = { &colPortB };
const uint8_t COL_PORT_COUNT = sizeof(ptrsColPorts)/sizeof(*ptrsColPorts);

// =================== CODES ===================
/*
The CODES section instantiates six codes, one for each item in the layout:
    s_a     s_exclamation   s_b     s_at
    l_fn                    s_shift
*/
// ---------------- LAYER CODE -----------------
enum layers { NORMAL, FN };

LayerState layerState;
Code_LayerHold l_fn(FN, layerState);

// ---------------- SCAN CODES -----------------
/*
The Code_Sc constructor takes one scancode ("Sc" means "scancode").
When Code_Sc is pressed, it sends its scancode.
*/
Code_Sc s_a(KEY_A);
Code_Sc s_b(KEY_B);
/*
The Code_ScS constructor takes one scancode to be shifted ("ScS" means "scancode shifted").
When Code_ScS is pressed, it calls Code_AutoShift before sending its scancode.
*/
Code_ScS s_exclamation(KEY_1);
Code_ScS s_at(KEY_2);

// ----------------- SHIFT CODE ----------------
/*
The Code_Shift constructor takes one scancode.
*/
Code_Shift s_shift(MODIFIERKEY_LEFT_SHIFT);

/*
Code_Shift pointers are placed in an array because most keyboards have a left and right shift.
This sketch only has one shift code.
*/
Code_Shift* const ptrsS[] = { &s_shift };

/*
Code_AutoShift is the base class of Codes_ScS (Codes_ScS is explained in the preceding section).
It has two static variables, ptrsShifts and shiftCount, which are defined here.
ptrsShifts is the array of Code_Shift pointers; one pointer for each shift key.
*/
Code_Shift* const* const Code_AutoShift::ptrsShifts = ptrsS;
const uint8_t Code_AutoShift::shiftCount = sizeof(ptrsShifts)/sizeof(*ptrsShifts);

/*
HOW AUTOSHIFT WORKS
When a modifier key is pressed, a standard keyboard driver will temporarily modify the normal action of another key when pressed together.
    KEY_1 writes '1'
    MODIFIERKEY_LEFT_SHIFT + KEY_1 writes '!'

    KEY_2 writes '2'
    MODIFIERKEY_LEFT_SHIFT + KEY_2 writes '@'

Code_ScS takes care of the MODIFIERKEY_LEFT_SHIFT automatically
When the user presses '!' or '@' on the fn layer:
    Code_AutoShift checks the position of each shift key
    Code_ScS sends MODIFIERKEY_LEFT_SHIFT scancode if needed
    Code_ScS sends its scancode
*/

// ================== MATRIX ===================
// ------------------- KEYS --------------------
Key* const ptrsCodes_00[] = { &s_a, &s_exclamation };
Key_LayeredKeysArray k_00(ptrsCodes_00);

Key* const ptrsCodes_01[] = { &s_b, &s_at };
Key_LayeredKeysArray k_01(ptrsCodes_01);

LayerStateInterface& Key_LayeredKeysArray::refLayerState = layerState;

// ------------------- ROWS --------------------
Key* const ptrsKeys_0[] = { &k_00, &k_01 };
Row row_0(rowPortF, 1<<0, ptrsColPorts, COL_PORT_COUNT, ptrsKeys_0);

Key* const ptrsKeys_1[] = { &l_fn,  &s_shift };
Row row_1(rowPortF, 1<<1, ptrsColPorts, COL_PORT_COUNT, ptrsKeys_1);

// ------------------ MATRIX -------------------
Row* const ptrsRows[] = { &row_0, &row_1 };
const uint8_t ROW_COUNT = sizeof(ptrsRows)/sizeof(*ptrsRows);

Matrix matrix(ptrsRows, ROW_COUNT, 1);

// ################### MAIN ####################
void setup()
{
    Keyboard.begin();
}

void loop()
{
    matrix.scan();
}
