/* keybrd_mapping_bb.ino

Runs on DodoHand hardware or breadboard, using the left matrix, first two rows and columns.
Uses the same variable naming convention as keybrd_DH.

| Layout | **0** | **1** |
|:------:|-------|-------|
|  **0** | a  !  | b  @  |
|  **1** | fn    | shift |
*/
// ################# GLOBAL ####################
// ================ INCLUDES ===================
//Arudino library files
#include <Wire.h>

//keybrd library files
//#include <objects_scancode.h>
#include <Code_Sc.h>
#include <Code_ScS.h>

#include <Code_Shift.h>
#include <StateLayers.h>
//#include <Code_LayerLock.h>
#include <Code_LayerHold.h>

#include <Key_LayeredKeysArray.h>

#include <RowPort_AVR_Optic.h>
#include <ColPort_AVR.h>

#include <Row.h>
#include <Matrix.h>

#include <Debug.h>

// ================= DEBUG =====================
Debug debug;

// =========== SPEED CONFUGURATIONS ============
const unsigned int Row::DELAY_MICROSECONDS = 1000;

// =============== LEFT PORTS ==================
RowPort_AVR_Optic rowPortF_L(DDRF, PORTF);

ColPort_AVR colPortB_L(DDRB, PORTB, PINB, 1<<0 | 1<<1 );

ColPort* const ptrsColPorts_L[] = { &colPortB_L };
const uint8_t COL_PORT_L_COUNT = sizeof(ptrsColPorts_L)/sizeof(*ptrsColPorts_L);

// ================= CODES =====================
// -------------- LAYER CODES ------------------
StateLayers stateLayer;
//Code_LayerLock l_alpha(0, stateLayer);
Code_LayerHold l_fn(1, stateLayer);

// --------------- SHIFT CODE ------------------
Code_Shift s_shift(MODIFIERKEY_LEFT_SHIFT);
Code_Shift *const ptrsShift[] = { &s_shift };
Code_Shift *const *const Code_AutoShift::ptrsShifts = ptrsShift;
const uint8_t Code_AutoShift::shiftCount = sizeof(ptrsShifts)/sizeof(*ptrsShifts);

// --------------- SCAN CODES ------------------
Code_Sc s_a(KEY_A);
Code_Sc s_b(KEY_B);
Code_ScS s_exclamation(KEY_1);
Code_ScS s_at(KEY_2);

StateLayersInterface& Key_LayeredKeysArray::refStateLayers = stateLayer;

// ============== LEFT MATRIX ==================
// --------------- LEFT KEYS -------------------
Key* const ptrsCodes_L00[] = { &s_a, &s_exclamation };
Key_LayeredKeysArray k_L00(ptrsCodes_L00);

Key* const ptrsCodes_L01[] = { &s_b, &s_at };
Key_LayeredKeysArray k_L01(ptrsCodes_L01);

// -------------- LEFT MAPPING -----------------
// the mapping layout array consumes no additional SRAM
/*
Key* const ptrsLayout[2][2] = { { &k_L00, &k_L01   },
                                { &l_fn,  &s_shift } };
*/
Key* const ptrsLayout[2][2] = { { &k_L01, &k_L00   }, //swapped keys a-b
                                { &l_fn,  &s_shift } };

// --------------- LEFT ROWS -------------------
Key* const ptrsKeys_L0[] = { ptrsLayout[0][0], ptrsLayout[0][1] };
Row row_L0(rowPortF_L, 1<<0, ptrsColPorts_L, COL_PORT_L_COUNT, ptrsKeys_L0);

Key* const ptrsKeys_L1[] = { ptrsLayout[1][0], ptrsLayout[1][1] };
Row row_L1(rowPortF_L, 1<<1, ptrsColPorts_L, COL_PORT_L_COUNT, ptrsKeys_L1);

// -------------- LEFT MATRIX ------------------
Row* const ptrsRows_L[] = { &row_L0, &row_L1 };
const uint8_t ROW_L_COUNT = sizeof(ptrsRows_L)/sizeof(*ptrsRows_L);

Matrix matrix_L(ptrsRows_L, ROW_L_COUNT, 1);

// ################## MAIN #####################
void setup()
{
    Keyboard.begin();
    delay(1000);        //time for OS to detect USB before printing
    Keyboard.print(F("keybrd_mapping_bb.ino, "));
    debug.print_free_RAM();
}

void loop()
{
    matrix_L.scan();
}
