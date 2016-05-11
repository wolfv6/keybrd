/* keybrd_4_split_with_IOE_annotated.ino

This sketch:
    is a simple 1-layer keyboard
    runs on two matrices of a breadboard keyboard
    is annotated with a walk-through narrative

This layout table shows left and right matrices:

| Left  | **0** | **1** | | Right | **0** | **1** |
|:-----:|-------|-------|-|:-----:|-------|-------|
| **0** | a     | b     | | **0** | 1     | 2     |
| **1** | shift | c     | | **1** | 3     | shift |

MARTIX NAMING CONVENTION
Since this keyboard has two matrices, we need a naming convention to distinguish the matrices.
Matrix IDs are the letters 'L' and 'R' (left and right).
Port object names and Port pointer array names end with matrix ID:
                        port1_R
    rowPortF_L          rowPort1_R
                        port0_R
    colPortB_L          colPort0_R
    ptrsColPorts_L      ptrsColPorts_R
    COL_PORT_L_COUNT    COL_PORT_R_COUNT

Key pointer array names and Row objects names end with matrix ID and row number:
    ptrsKeys_L0         ptrsKeys_R0
    row_L0              row_R0

Matrix object names end with matrix ID:
    matrix_L            matrix_R
*/
// ################## GLOBAL ###################
// ================= INCLUDES ==================
//Ports
#include <RowPort_AVR_Optic.h>
#include <ColPort_AVR.h>
#include <IOExpanderPort.h>
#include <RowPort_PCA9655E.h>
#include <ColPort_PCA9655E.h>

//Codes
#include <Code_Sc.h>

//Matrix
#include <Row.h>
#include <Matrix.h>

// ============ SPEED CONFIGURATIONS ============
const unsigned int Row::DELAY_MICROSECONDS = 1000;

// ================ LEFT PORTS =================
/*
The left matrix is scanned by a micro-controller.
*/
RowPort_AVR_Optic rowPortF_L(DDRF, PORTF);

ColPort_AVR colPortB_L(DDRB, PORTB, PINB, 1<<0 | 1<<1 );
ColPort* const ptrsColPorts_L[] = { &colPortB_L };
const uint8_t COL_PORT_L_COUNT = sizeof(ptrsColPorts_L)/sizeof(*ptrsColPorts_L);

// =============== RIGHT PORTS =================
/*
The right matrix is scanned by an I/O expander.

The micro-controller and I/O expander use address 0x18 to communicate with each other over I2C.
ADDR is a static variable of class IOExpanderPort.
*/
const uint8_t IOExpanderPort::ADDR = 0x18;

/*
The I/O expander has two ports.  Each port has eight pins.
One port is connected to the matrix's rows.  The other port is connected to the matrix's columns.

The IOExpanderPort constructor parameters specify the port number and initial output value.
I/O Expander and AVR have similar constructor parameters for RowPort and ColPort.

port1_R is port 1 and has an initial output value of 0.
rowPort1_R uses port1_R.
*/
IOExpanderPort port1_R(1, 0);
RowPort_PCA9655E rowPort1_R(port1_R);

/*
port0_R is port 0 and has an initial output value of 0.
colPort0_R uses port0_R to read pin 0 and pin 1.
*/
IOExpanderPort port0_R(0, 0);
ColPort_PCA9655E colPort0_R(port0_R, 1<<0 | 1<<1 );

/*
ColPort pointers are packed into an array.
*/
ColPort* const ptrsColPorts_R[] = { &colPort0_R };
const uint8_t COL_PORT_R_COUNT = sizeof(ptrsColPorts_R)/sizeof(*ptrsColPorts_R);

// =================== CODES ===================
/*
Codes are not grouped into left and right because codes are independent of layout.
    - a keyboard can have differnt layouts
    - some codes may appear on both matrices
*/
Code_Sc s_shiftL(MODIFIERKEY_LEFT_SHIFT);
Code_Sc s_shiftR(MODIFIERKEY_RIGHT_SHIFT);

Code_Sc s_a(KEY_A);
Code_Sc s_b(KEY_B);
Code_Sc s_c(KEY_C);
Code_Sc s_1(KEY_1);
Code_Sc s_2(KEY_2);
Code_Sc s_3(KEY_3);

// ================ LEFT MATRIX ================
// ---------------- LEFT ROWS ------------------
Key* const ptrsKeys_L0[] = { &s_a, &s_b };
Row row_L0(rowPortF_L, 1<<0, ptrsColPorts_L, COL_PORT_L_COUNT, ptrsKeys_L0);

Key* const ptrsKeys_L1[] = { &s_c,  &s_shiftL };
Row row_L1(rowPortF_L, 1<<1, ptrsColPorts_L, COL_PORT_L_COUNT, ptrsKeys_L1);

// ---------------- LEFT MATRIX ----------------
Row* const ptrsRows_L[] = { &row_L0, &row_L1 };
const uint8_t ROW_L_COUNT = sizeof(ptrsRows_L)/sizeof(*ptrsRows_L);

Matrix matrix_L(ptrsRows_L, ROW_L_COUNT, 1);

// ================ RIGHT MATRIX ===============
// ---------------- RIGHT ROWS -----------------
Key* const ptrsKeys_R0[] = { &s_1, &s_2 };
Row row_R0(rowPort1_R, 1<<0, ptrsColPorts_R, COL_PORT_R_COUNT, ptrsKeys_R0);

Key* const ptrsKeys_R1[] = { &s_3,  &s_shiftR };
Row row_R1(rowPort1_R, 1<<1, ptrsColPorts_R, COL_PORT_R_COUNT, ptrsKeys_R1);

// ---------------- RIGHT MATRIX ---------------
Row* const ptrsRows_R[] = { &row_R0, &row_R1 };
const uint8_t ROW_R_COUNT = sizeof(ptrsRows_R)/sizeof(*ptrsRows_R);

Matrix matrix_R(ptrsRows_R, ROW_R_COUNT, 1);

// ################### MAIN ####################
void setup()
{
/*
Call begin() for I/O expander's rowPort and colPort.
*/
    rowPort1_R.begin();
    colPort0_R.begin();
    Keyboard.begin();
}

/*
loop() continually scans both Matrix objects.
*/
void loop()
{
    matrix_L.scan();
    matrix_R.scan();
}
