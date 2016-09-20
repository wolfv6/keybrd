/* keybrd_3d_sublayerNested.ino

This sketch:
    is firmware for a simple 2-layer keyboard
    runs on the first two rows and columns of a breadboard keyboard

| Layout | **0** | **1** | **2** |
|:------:|:-----:|:-----:|:-----:|
|  **0** | a - 1 | b =   | c Num |
|  **1** |Normal | Sym   | Enter |

normal layer keys are a b c
sym layer keys are brackets [ ] and num
num layer keys are 6 7
The num layer key is located on the sym layer
num layer is active while holding sym+num

Each cell in the table's body represents a key.
The layered keys in column 1 have two layers; one character for each layer.
Letters 'a' and 'b' are on the normal layer.  Numbers '1' and '2' are on the fn layer.
Holding the fn key down makes it the active layer.  Releasing the fn key restores the normal layer.
*/
// ################## GLOBAL ###################
// ================= INCLUDES ==================
//Keys
#include <Code_Sc.h>
#include <Code_Null.h>
#include <LayerState.h>
#include <Code_LayerLock.h>
#include <Code_LayerHold.h>
#include <Key_LayeredKeys.h>
#include <Key_LayeredScSc.h>

//Matrix
#include <Row.h>
#include <Scanner_uC.h>
#include <ScanDelay.h>

// ============ SPEED CONFIGURATION ============
ScanDelay scanDelay(9000);

// ================== SCANNER ==================
uint8_t readPins[] = {14, 15, 16};
uint8_t readPinCount = sizeof(readPins)/sizeof(*readPins);

Scanner_uC scanner(LOW, readPins, readPinCount);

/* =================== CODES ===================
The CODES section instantiates six codes, one for each item in the layout.
*/
/* ---------------- LAYER CODE -----------------
enum assigns layerId numbers to the layers.
*/
enum layers { NORMAL, SYM };

/* layerState keeps track of the active layer.
*/
LayerState layerState;

LayerStateInterface& Key_LayeredKeys::refLayerState = layerState;
/*
NORMAL=0 and FN=1.  LayerState's default layerId is 0.
The Code_LayerHold constructor has two parameters:
 1) the layerId that will be active while the key is held down
 2) a LayerState that will keep track of the active layer
When l_fn is pressed, it tells layerState to change the active layer to 1.
When l_fn is released, it tells layerState that layer 1 is released, and layerState restores the default layer.
*/
Code_LayerLock l_normal(NORMAL, layerState);
Code_LayerLock l_sym(SYM, layerState);

//sublayer
enum subLayers { SUBSYM, SUBNUM };

LayerState sublayerState;

Code_LayerHold l_num(SUBNUM, sublayerState);

LayerStateInterface& Key_LayeredScSc::refLayerState = sublayerState;

// ---------------- SCAN CODES -----------------
Code_Sc s_a(KEY_A);
Code_Sc s_b(KEY_B);
Code_Sc s_c(KEY_C);

Code_Sc s_minus(KEY_MINUS);
Code_Sc s_equal(KEY_EQUAL);
Code_Sc s_enter(KEY_ENTER);

Code_Sc s_1(KEY_1);
Code_Null code_null;

/* =================== KEYS ====================
Here we pack Codes into keys.
The Key_LayeredKeys constructor takes one array of Code pointers - one Code object per layer.

The Key object names in this sketch start with a "k_" followed by row-column coordinates.
*/

Key_LayeredScSc sub_00(KEY_MINUS, KEY_1);
Key* const ptrsCodes_00[] = { &s_a, &sub_00 };
Key_LayeredKeys k_00(ptrsCodes_00);

Key* const ptrsCodes_01[] = { &s_b, &s_equal };
Key_LayeredKeys k_01(ptrsCodes_01);

Key* const ptrsCodes_02[] = { &s_c, &l_num };
Key_LayeredKeys k_02(ptrsCodes_02);

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
Key* const ptrsKeys_0[] = { &k_00, &k_01, &k_02 };
uint8_t keyCount_0 = sizeof(ptrsKeys_0)/sizeof(*ptrsKeys_0);
Row row_0(scanner, 0, ptrsKeys_0, keyCount_0);

Key* const ptrsKeys_1[] = { &l_normal, &l_sym, &s_enter };
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
