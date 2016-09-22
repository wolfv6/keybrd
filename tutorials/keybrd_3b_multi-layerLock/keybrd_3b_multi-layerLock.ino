/* keybrd_3b_multi-layerLock.ino

This sketch:
    is firmware for a simple 2-layer keyboard
    runs on the first two rows and columns of a breadboard keyboard

| Layout | **0** | **1** |
|:------:|:-----:|:-----:|
|  **0** | a  -  | b  =  |
|  **1** | Alpha |  Sym  |

Pressing the "Alpha" layer key locks the Alpha layer.
Letters 'a' 'b' are on the Alpha layer.

Pressing the "Sym" layer key locks the Sym layer.
Symbols '-' '=' are on the Sym layer.
*/
// ################## GLOBAL ###################
// ================= INCLUDES ==================
//Keys
#include <Code_Sc.h>
#include <LayerState.h>
#include <Code_LayerLock.h>
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
enum layers { ALPHA, SYM };

LayerState layerState;

/*
The Code_LayerLock constructor has two parameters:
 1) the layerId that becomes the active layer when the key is pressed 
 2) a LayerState that will keep track of the active layer
When l_normal is pressed, ALPHA becomes the active layer.
When l_sym is pressed, SYM becomes the active layer.
*/
Code_LayerLock l_normal(ALPHA, layerState);
Code_LayerLock l_sym(SYM, layerState);

// ---------------- SCAN CODES -----------------
Code_Sc s_a(KEY_A);
Code_Sc s_b(KEY_B);
Code_Sc s_minus(KEY_MINUS);
Code_Sc s_equal(KEY_EQUAL);

// =================== KEYS ====================
Key* const ptrsKeys_00[] = { &s_a, &s_minus };
Key_LayeredKeys k_00(ptrsKeys_00);

Key* const ptrsKeys_01[] = { &s_b, &s_equal };
Key_LayeredKeys k_01(ptrsKeys_01);

LayerStateInterface& Key_LayeredKeys::refLayerState = layerState;

// =================== ROWS ====================
Key* const ptrsKeys_0[] = { &k_00, &k_01 };
uint8_t keyCount_0 = sizeof(ptrsKeys_0)/sizeof(*ptrsKeys_0);
Row row_0(scanner, 0, ptrsKeys_0, keyCount_0);

Key* const ptrsKeys_1[] = { &l_normal, &l_sym };
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
