/* keybrd_3_multi-layer_annotated.ino

This sketch:
    is firmware for a simple 2-layer keyboard
    runs on the first two rows and columns of a breadboard keyboard

| Layout | **0** | **1** |
|:------:|-------|-------|
|  **0** | shift | a  1  |
|  **1** |  fn   | b  2  |

Each cell in the table's body represents a key.
The layered keys in row 0 have two layers; one character for each layer.
Letters 'a' and 'b' are on the normal layer.  Numbers '1' and '2' are one the fn layer.
Holding the fn key down makes it the active layer.  Releasing the fn key restores the normal layer.
*/
// ################## GLOBAL ###################
// ================= INCLUDES ==================
//Keys
#include <Code_Sc.h>
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

/* =================== CODES ===================
The CODES section instantiates six codes, one for each item in the layout.
*/
/* ---------------- LAYER CODE -----------------
enum assigns id numbers to the layers.
*/
enum layers { NORMAL, FN };

/* layerState keeps track of the active layer.
*/
LayerState layerState;

/*
NORMAL=0 and FN=1.  LayerState's default layer id is 0.
The Code_LayerHold constructor has two parameters:
 1) the layer that will be active while the key is held down. 
 2) the LayerState
When l_fn is pressed, it tells layerState to change the active layer to 1.
When l_fn is released, it tells layerState that layer 1 is released, and layerState restores the default layer.
*/
Code_LayerHold l_fn(FN, layerState);

// ---------------- SCAN CODES -----------------
Code_Sc s_a(KEY_A);
Code_Sc s_b(KEY_B);
Code_Sc s_1(KEY_1);
Code_Sc s_2(KEY_2);
Code_Sc s_shift(MODIFIERKEY_LEFT_SHIFT);

/* =================== KEYS ====================
Here we pack Codes into keys.
The Key_LayeredKeysArray constructor takes one array of Code pointers - one Code object per layer.
Key_LayeredKeysArray uses layer id numbers as array indexes.
Thus Key_LayeredKeysArray calls the Code corresponding to the active layer id.

The Key object names in this sketch start with a "k_" followed by matrix-row-column coordinates.
*/
Key* const ptrsCodes_01[] = { &s_a, &s_1 };
Key_LayeredKeysArray k_01(ptrsCodes_01);

Key* const ptrsCodes_11[] = { &s_b, &s_2 };
Key_LayeredKeysArray k_11(ptrsCodes_11);

/* Key_LayeredKeysArray has a reference to layerState.
Thus Key_LayeredKeysArray can call layerState to get the active layer id.
*/
LayerStateInterface& Key_LayeredKeysArray::refLayerState = layerState;

/* HOW LAYERED OBJECTS WORK
When a Key_LayeredKeysArray object is pressed, it gets the active layer id from layerState
It then uses the layer id as an array index to send the scancode for the active layer.
*/

/* =================== ROWS ====================
Here we pack Key pointers into row objects.

Codes are a kind of Key that only have one layer.
So rows can contain a mix of multi-layered keys and codes.
Arrays ptrsKeys_0[] and ptrsKeys_1[] contain both Key pointers and Code pointers.
*/
Key* const ptrsKeys_0[] = { &s_shift, &k_01 };
Row_uC row_0(0, readPins, READ_PIN_COUNT, ptrsKeys_0);

Key* const ptrsKeys_1[] = { &l_fn, &k_11 };
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
