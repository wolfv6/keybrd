/* keybrd_7b_mapping_multi-layer.ino

This sketch:
    is modified from keybrd_3a_multi-layerHold.ino by swaping readPins numbers with Row-pin numbers
    runs on basic breadboard keyboard modified by flipping diodes, anodes towards rows (blue bus)
    demonstrates mapping from LAYOUT to MATRIX on a multi-layer keyboard
    assumes you undstand keybrd Tutorial 2 - keybrd multi-layer

| Layout | **0** | **1** |
|:------:|-------|-------|
|  **0** | a  -  | b  =  |
|  **1** |  fn   | shift |
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
uint8_t readPins[] = {0, 1};
uint8_t readPinCount = sizeof(readPins)/sizeof(*readPins);

Scanner_uC scanner(LOW, readPins, readPinCount);

// =================== CODES ===================
// ---------------- LAYER CODE -----------------
enum layerIds { NORMAL, FN };

LayerState layerState;

Code_LayerHold l_fn(FN, layerState);

// ---------------- SCAN CODES -----------------
Code_Sc s_a(KEY_A);
Code_Sc s_b(KEY_B);
Code_Sc s_minus(KEY_MINUS);
Code_Sc s_equal(KEY_EQUAL);
Code_Sc s_shift(MODIFIERKEY_LEFT_SHIFT);

/* ================== LAYOUT ===================
Keyboard layout is the placement of keys.
nullptrs are place holders that are not mapped to the matrix.
By convention, single-layer keys are placed on layer0, and nulls are placed in the remaining layers.
If you replace a null with a code, make sure its coordinate is in the KEYS MAPPING section.
Each non-nullptr array element consums 4 bytes of SRAM (on Teensy LC 32 bit controller).
*/
Key* const ptrsLayout[2][2][2] = { //[layer][row][col]
 //layer0
 {//col0      col1
  { &s_a,     &s_b },       //row0
  { &l_fn,    &s_shift }    //row1
 },
 //layer1
 {//col0      col1
  { &s_minus, &s_equal },   //row0
  { nullptr,  nullptr }     //row1
 }
};

/* ================== MATRIX ===================
ptrsLayout[layer][row][col] coordinates correspond to the elements in the layout.

// --------------- CODE MAPPINGS ---------------
Each ptrsLayout in this section maps a Code to one layer in a Key.
Only Key_LayeredKeys are instantiated in this section.
*/
Key* const ptrsKeys_00[] = { ptrsLayout[0][0][0], ptrsLayout[1][0][0] }; // { &s_a, &s_minus };
Key_LayeredKeys k_00(ptrsKeys_00);

Key* const ptrsKeys_01[] = { ptrsLayout[0][0][1], ptrsLayout[1][0][1] }; // { &s_b, &s_equal };
Key_LayeredKeys k_01(ptrsKeys_01);

LayerStateInterface& Key_LayeredKeys::refLayerState = layerState;

/* --------------- KEY MAPPINGS ----------------
The Keys are transposed (layout rows are placed in matrix columns).
ptrsLayout elements are from the LAYOUT section.
Key_LayeredKeys are from the CODE MAPPINGS section.
*/
Key* const ptrsKeys_0[] = { &k_00, ptrsLayout[0][1][0] }; // { { &s_a, &s_minus }, &l_fn };
uint8_t keyCount_0 = sizeof(ptrsKeys_0)/sizeof(*ptrsKeys_0);
Row row_0(scanner, 14, ptrsKeys_0, keyCount_0);

Key* const ptrsKeys_1[] = { &k_01, ptrsLayout[0][1][1] }; // { { &s_b, &s_equal }, &s_shift };
uint8_t keyCount_1 = sizeof(ptrsKeys_1)/sizeof(*ptrsKeys_1);
Row row_1(scanner, 15, ptrsKeys_1, keyCount_1);

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
