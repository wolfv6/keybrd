/* keybrd_3a_multi-layerHold.ino

This sketch:
    is firmware for a simple 2-layer keyboard
    runs on the first two rows and columns of a breadboard keyboard

| Layout | **0** | **1** |
|:------:|-------|-------|
|  **0** | a  -  | b  =  |
|  **1** |  fn   | shift |

Each cell in the table's body represents a key.
The keys in column 1 have two characters each, one character for each layer.
"fn" is a layer key.  Holding the fn key down makes it the active layer. 
Releasing the fn key restores the normal layer.
Letters 'a' and 'b' are on the normal layer.  Symbols '-' and '=' are on the fn layer.
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

// =================== CODES ===================
/* ---------------- LAYER CODE -----------------
enum assigns layerId numbers to the layers.
NORMAL=0 and FN=1.  LayerState's default layerId is 0.
*/
enum layers { NORMAL, FN };

/*
layerState keeps track of the active layer.
*/
LayerState layerState;

/*
The Code_LayerHold constructor has two parameters:
 1) the layerId that will be the active layer while the key is held down
 2) a LayerState that will keep track of the active layer
When l_fn is pressed, it tells layerState to change the active layer to FN.
When l_fn is released, it tells layerState that layer FN is released,
and layerState restores the active layer to NORMAL (sets active layer to the default layerId 0).
*/
Code_LayerHold l_fn(FN, layerState);

// ---------------- SCAN CODES -----------------
Code_Sc s_a(KEY_A);
Code_Sc s_b(KEY_B);
Code_Sc s_minus(KEY_MINUS);
Code_Sc s_equal(KEY_EQUAL);
Code_Sc s_shift(MODIFIERKEY_LEFT_SHIFT);

/* =================== KEYS ====================
Here we pack Codes into keys.
The Key_LayeredKeys constructor takes one array of Code pointers - one Code object per layer.

The Key object names in this sketch start with a "k_" followed by row-column coordinates.
*/
Key* const ptrsCodes_00[] = { &s_a, &s_minus };
Key_LayeredKeys k_00(ptrsCodes_00);

Key* const ptrsCodes_01[] = { &s_b, &s_equal };
Key_LayeredKeys k_01(ptrsCodes_01);

/*
Key_LayeredKeys has a reference to layerState.
*/
LayerStateInterface& Key_LayeredKeys::refLayerState = layerState;

/* HOW LAYERED OBJECTS WORK
When a Key_LayeredKeys object is pressed, it gets the active layer id from layerState.
It then uses the layer id as an array index to call the Code of the active layer.
The Code object then sends its scancode over USB.
*/

/* =================== ROWS ====================
Here we pack Key pointers into row objects.

Rows are composed of a Key-pointer array.
Codes are a kind of Key that only have one layer.
Thus rows can contain a mix of codes and multi-layered keys (subtype polymorphism).
In this example, Key-pointer arrays contain both Code pointers (&s_shift and &l_fn)
and Key pointers (&k_01 and &k_11).
*/
Key* const ptrsKeys_0[] = { &k_00, &k_01 };
uint8_t keyCount_0 = sizeof(ptrsKeys_0)/sizeof(*ptrsKeys_0);
Row row_0(scanner, 0, ptrsKeys_0, keyCount_0);

Key* const ptrsKeys_1[] = { &l_fn, &s_shift };
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
