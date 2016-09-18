/* keybrd_3_multi-layer_annotated.ino

This sketch:
    is firmware for a simple 2-layer keyboard
    runs on the first two rows and columns of a breadboard keyboard

| Layout | **0** | **1** |
|:------:|-------|-------|
|  **0** | shift | a  1  |
|  **1** |  fn   | b  2  |

Each cell in the table's body represents a key.
The layered keys in column 1 have two layers; one character for each layer.
Letters 'a' and 'b' are on the normal layer.  Numbers '1' and '2' are on the fn layer.
Holding the fn key down makes it the active layer.  Releasing the fn key restores the normal layer.
*/
// ################## GLOBAL ###################
// ================= INCLUDES ==================
//Keys
#include <Code_Sc.h>
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
 1) the layer that will be active while the key is held down
 2) a LayerState that will keep track of the active layer
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
The Key_LayeredKeys constructor takes one array of Code pointers - one Code object per layer.

The Key object names in this sketch start with a "k_" followed by row-column coordinates.
*/
Key* const ptrsCodes_01[] = { &s_a, &s_1 };
Key_LayeredKeys k_01(ptrsCodes_01);

Key* const ptrsCodes_11[] = { &s_b, &s_2 };
Key_LayeredKeys k_11(ptrsCodes_11);

/* Key_LayeredKeys has a reference to layerState.
Thus Key_LayeredKeys can call layerState to get the active layer id.
*/
LayerStateInterface& Key_LayeredKeys::refLayerState = layerState;

/* HOW LAYERED OBJECTS WORK
When a Key_LayeredKeys object is pressed, it gets the active layer id from layerState.
It then uses the layer id as an array index to call the Code of the active layer.
The Code object then sends its scancode over USB.
*/

/* =================== ROWS ====================
Here we pack Key pointers into row objects.

Codes are a kind of Key that only have one layer.
So rows can contain a mix of codes and multi-layered keys.
Arrays ptrsKeys_0[] and ptrsKeys_1[] contain both Code pointers and Key pointers.
*/
Key* const ptrsKeys_0[] = { &s_shift, &k_01 };
uint8_t keyCount_0 = sizeof(ptrsKeys_0)/sizeof(*ptrsKeys_0);
Row row_0(scanner, 0, ptrsKeys_0, keyCount_0);

Key* const ptrsKeys_1[] = { &l_fn, &k_11 };
uint8_t keyCount_1 = sizeof(ptrsKeys_1)/sizeof(*ptrsKeys_1);
Row row_1(scanner, 1, ptrsKeys_1, keyCount_1);

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
