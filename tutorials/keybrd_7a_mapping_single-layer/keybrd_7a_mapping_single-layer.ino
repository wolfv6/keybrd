/*  keybrd_7a_mapping_single-layer.ino

This sketch:
    is modified from keybrd_2_single.ino by swaping readPins numbers with Row-pin numbers
    runs on basic breadboard keyboard modified by flipping diodes, anodes towards rows (blue bus)
    demonstrates mapping from LAYOUT to MATRIX on a single-layer keyboard

| Layout | **0** | **1** |
|:------:|-------|-------|
|  **0** |   1   |   2   |
|  **1** |   a   |   b   |
*/
// ################## GLOBAL ###################
// ================= INCLUDES ==================
#include <Code_Sc.h>
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
Code_Sc s_a(KEY_A);
Code_Sc s_b(KEY_B);
Code_Sc s_1(KEY_1);
Code_Sc s_2(KEY_2);

/* ================== LAYOUT ===================
Keyboard layout is the placement of keys.
*/
Key* const ptrsLayout[2][2] = { //[row][col]
 //col0     col1
 { &s_1,    &s_2 },     //row0
 { &s_a,    &s_b }      //row1
};

/* ================== MATRIX ===================
// --------------- KEY MAPPINGS ----------------
ptrsLayout[row][col] coordinates correspond to the elements in the layout.
The Keys are transposed (layout rows are placed in matrix columns).
*/
Key* ptrsKeys_0[] = { ptrsLayout[0][0], ptrsLayout[1][0] };
uint8_t keyCount_0 = sizeof(ptrsKeys_0)/sizeof(*ptrsKeys_0);
Row row_0(scanner, 14, ptrsKeys_0, keyCount_0);

Key* ptrsKeys_1[] = { ptrsLayout[0][1], ptrsLayout[1][1] };
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
