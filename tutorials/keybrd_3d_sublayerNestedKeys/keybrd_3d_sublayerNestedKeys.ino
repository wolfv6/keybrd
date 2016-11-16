/* keybrd_3d_sublayerNested.ino

This sketch:
    is firmware for layout with two layers plus one sublayer.
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

/* =================== CODES ===================
Each LayerState object can manage one layer group.  This sketch uses two LayerState objects.
*/
// ---------------- LAYER GROUP ----------------
enum layers { ALPHA, SYM };

/*
groupState keeps track of a layer group's active layer.
*/
LayerState groupState;

/*
groupState is assigned to layers ALPHA and SYM.
*/
Code_LayerLock l_alpha(ALPHA, groupState);
Code_LayerLock l_sym(SYM, groupState);

/*
groupState manages a layer group delineated by all layers that are in Key_LayeredKeys objects.
*/
LayerStateInterface& Key_LayeredKeys::refLayerState = groupState;

// --------------- LAYER SUBGROUP --------------
enum subLayers { SUBSYM, SUBNUM };

/*
subgroupState keeps track of a layer subgroup's active layer.
*/
LayerState subgroupState;

/*
subgroupState is assigned to layer SUBNUM.
subgroupState also has a default layer 0, which implicitly is layer SUBSYM.
*/
Code_LayerHold l_num(SUBNUM, subgroupState);

/*
Key_LayeredKeys and Key_LayeredKeys1 are identical classes with distinct static refLayerState.
subgroupState manages a layer group delineated by all layers that are in Key_LayeredKeys1 objects.
*/
LayerStateInterface& Key_LayeredKeys1::refLayerState = subgroupState;

// ---------------- SCAN CODES -----------------
Code_Sc s_a(KEY_A);
Code_Sc s_b(KEY_B);
Code_Sc s_c(KEY_C);

Code_Sc s_minus(KEY_MINUS);
Code_Sc s_equal(KEY_EQUAL);
Code_Sc s_enter(KEY_ENTER);

Code_Sc s_1(KEY_1);

/* =================== KEYS ====================
k_sub00 contains codes for sub layers SUBSYM and SUBNUM.
k_sub00 gets it's active layer from subgroupState.
(The Num sublayer only has one key because small example.  Usually sublayers have multiple keys.)
*/
Key* const ptrsKeys_sub00[] = { &s_minus, &s_1 };
Key_LayeredKeys1 k_sub00(ptrsKeys_sub00);

/*
k_00 contains code and key for layers ALPHA and SYM.
k_00 gets it's active layer from groupState.
k_sub00 is nested in layer SYM.
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

Key* const ptrsKeys_1[] = { &l_alpha, &l_sym, &s_enter };
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
