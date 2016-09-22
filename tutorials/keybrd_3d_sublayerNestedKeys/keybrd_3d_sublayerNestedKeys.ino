/* keybrd_3d_sublayerNested.ino

This sketch:
    is firmware for layout with 2 layers plus 1 sublayer.
    runs on the first three columns of a breadboard keyboard

| Layout | **0** | **1** | **2** |
|:------:|:-----:|:-----:|:-----:|
|  **0** | a - 1 | b =   | c Num |
|  **1** | Alpha |  Sym  | Enter |

*/
// ################## GLOBAL ###################
// ================= INCLUDES ==================
//Keys
#include <Code_Sc.h>
#include <LayerState.h>
#include <Code_LayerLock.h>
#include <Code_LayerHold.h>
#include <Key_LayeredKeys.h>
#include <Key_LayeredKeys1.h>

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

// =================== CODES ===================
// ----------------- LAYER CODE ----------------
enum layers { ALPHA, SYM };

LayerState layerState;

Code_LayerLock l_normal(ALPHA, layerState);
Code_LayerLock l_sym(SYM, layerState);

/*
Key_LayeredKeys are associated with layerState.
*/
LayerStateInterface& Key_LayeredKeys::refLayerState = layerState;

/* ---------------- SUBLAYER CODE --------------
Sublayers are implemented just like primary layers.
*/
enum subLayers { SUBSYM, SUBNUM };

LayerState sublayerState;

Code_LayerHold l_num(SUBNUM, sublayerState);

/*
Key_LayeredKeys1 are associated with sublayerState.
Key_LayeredKeys (in layer) and Key_LayeredKeys1 (in sublayer) classes are nearly identical,
only the static refLayerState are different.
*/
LayerStateInterface& Key_LayeredKeys1::refLayerState = sublayerState;

// ---------------- SCAN CODES -----------------
Code_Sc s_a(KEY_A);
Code_Sc s_b(KEY_B);
Code_Sc s_c(KEY_C);

Code_Sc s_minus(KEY_MINUS);
Code_Sc s_equal(KEY_EQUAL);
Code_Sc s_enter(KEY_ENTER);

Code_Sc s_1(KEY_1);

/* =================== KEYS ====================
The key k_sub00 contains codes for layerIds SUBSYM and SUBNUM.
(The Num sublayer only has one key because small example.  Usually sublayers have multiple keys.)
*/
Key* const ptrsKeys_sub00[] = { &s_minus, &s_1 };
Key_LayeredKeys1 k_sub00(ptrsKeys_sub00);

/*
k_sub00 is nested in k_00.
The key k_00 contains code and key for layerIds ALPHA and SYM.
Notice that k_sub00 is of type Key_LayeredKeys1, while k_00 is of type Key_LayeredKeys.
k_sub00 and k_00 are associated with distinct LayerStates.
*/
Key* const ptrsKeys_00[] = { &s_a, &k_sub00 };
Key_LayeredKeys k_00(ptrsKeys_00);

Key* const ptrsKeys_01[] = { &s_b, &s_equal };
Key_LayeredKeys k_01(ptrsKeys_01);

Key* const ptrsKeys_02[] = { &s_c, &l_num };
Key_LayeredKeys k_02(ptrsKeys_02);

// =================== ROWS ====================
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
