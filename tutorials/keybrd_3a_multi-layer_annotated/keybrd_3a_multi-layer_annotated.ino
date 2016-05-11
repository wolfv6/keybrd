/* keybrd_3_multi-layer_annotated.ino

This sketch:
    is a simple 2-layer keyboard
    runs on the first two rows and columns of a breadboard keyboard
    is annotated with a walk-through narrative

This layout table shows how keys are arranged on the keyboard:

| Layout | **0** | **1** |
|:------:|-------|-------|
|  **0** | a  1  | b  2  |
|  **1** | fn    | shift |

The layout's row and column numbers are in the headers.
Each cell in the table's body represents a key.
The layered keys in row 0 have two layers; one character for each layer.
Letters 'a' and 'b' are on the normal layer.  Numbers '1' and '2' are one the fn layer.
Holding the fn key down makes it the active layer.  Releasing the fn key restores the normal layer.
*/
// ################## GLOBAL ###################
// ================= INCLUDES ==================
//Ports
#include <RowPort_AVR_Optic.h>
#include <ColPort_AVR.h>

//Codes
#include <Code_Sc.h>
#include <StateLayers.h>
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
    s_a     s_1     s_b     s_2
    l_fn            s_shift
*/
// ---------------- LAYER CODE -----------------
/*
enum assings ID numbers to the layers.
*/
enum layers { NORMAL, FN };
/*
stateLayer keeps track of the active layer.  The default layer number is 0.
*/
StateLayers stateLayer;
/*
The Code_LayerHold constructor parameter specifies a layer ID number and a StateLayer.
When l_fn is pressed, it tells stateLayer to change the active layer to 1.
When l_fn is released, it tells stateLayer to restore the normal layer.
*/
Code_LayerHold l_fn(FN, stateLayer);

// ---------------- SCAN CODES -----------------
Code_Sc s_a(KEY_A);
Code_Sc s_b(KEY_B);
Code_Sc s_1(KEY_1);
Code_Sc s_2(KEY_2);
Code_Sc s_shift(MODIFIERKEY_LEFT_SHIFT);

// ================== MATRIX ===================
/*
The MATRIX section instantiates the components of the matrix:
    Codes are grouped into keys.
    Keys are grouped into rows.
    Rows are grouped into a matrix.
*/
// ------------------- KEYS --------------------
/*
Here we group Code pointers into keys.
Array ptrsCodes_00[] contains two pointers to Code objects.

Key_LayeredKeysArray constructor parameters are:
    one array of Code pointers

Key_LayeredKeysArray objects are multi-layered - one Code object per layer.
Layer ID numbers are array indexes for the Key_LayeredKeysArray.
Defining layer ID numbers with enum insures that they are a series of intergers starting at 0.

The Key object names in this sketch start with a "k_" followed by matrix-row-column coordinates.
*/
Key* const ptrsCodes_00[] = { &s_a, &s_1 };
Key_LayeredKeysArray k_00(ptrsCodes_00);

Key* const ptrsCodes_01[] = { &s_b, &s_2 };
Key_LayeredKeysArray k_01(ptrsCodes_01);

/*
Key_LayeredKeysArray has a static variable refStateLayers defined here.
It is a reference to stateLayer.
*/
StateLayersInterface& Key_LayeredKeysArray::refStateLayers = stateLayer;

/*
HOW LAYERED OBJECTS WORK
When a Key_LayeredKeysArray object is pressed,
 it gets the active layer from stateLayer and then sends the scancode for the active layer.
*/

// ------------------- ROWS --------------------
/*
Here we group Key pointers into rows.
Array ptrsKeys_0[] contains two pointers to Key_LayeredKeyArray objects.
*/
Key* const ptrsKeys_0[] = { &k_00, &k_01 };
Row row_0(rowPortF, 1<<0, ptrsColPorts, COL_PORT_COUNT, ptrsKeys_0);

/*
Codes are a kind of Key that only have one layer.
So rows can contain multi-leyered a mix of keys and codes.
Array ptrsKeys_1[] contains two Code pointers.
*/
Key* const ptrsKeys_1[] = { &l_fn,  &s_shift };
Row row_1(rowPortF, 1<<1, ptrsColPorts, COL_PORT_COUNT, ptrsKeys_1);

// ------------------ MATRIX -------------------
/*
Here we group Row pointers into a matrix.
Array ptrsRows[] contains two pointers to Row objects.
*/
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
