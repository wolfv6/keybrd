/* keybrd_6_active_high.ino

This sketch:
    is the tutorial 2 sketch with STROBE_ON/STROBE_OFF values swapped
    is active high 1-layer keyboard
    runs on the first two rows and columns of a active-high breadboard keyboard

| Layout | **0** | **1** |
|:------:|-------|-------|
|  **0** | shift | a     |
|  **1** | b     | c     |
*/

// ################## GLOBAL ###################
// ================= INCLUDES ==================
#include <ScanDelay.h>
#include <Code_Sc.h>
#include <Row_uC.h>

// ============ SPEED CONFIGURATION ============
ScanDelay scanDelay(9000);

/* ================ ACTIVE STATE ===============
STROBE_ON and STROBE_OFF define the logic levels for the strobe.
"Active high" means that if a switch is pressed (active), the read pin is high.
To make this sketch active high, STROBE_ON should be HIGH.

Compared active low, STROBE_ON/STROBE_OFF values swapped.
*/
const bool Scanner_uC::STROBE_ON = HIGH; //set matrix for active high
const bool Scanner_uC::STROBE_OFF = LOW;

// ================= PINS =================
uint8_t readPins[] = {14, 15};
uint8_t READ_PIN_COUNT = sizeof(readPins)/sizeof(*readPins);

// =================== CODES ===================
Code_Sc s_a(KEY_A);
Code_Sc s_b(KEY_B);
Code_Sc s_c(KEY_C);
Code_Sc s_shift(MODIFIERKEY_LEFT_SHIFT);

// =================== ROWS ====================
Key* ptrsKeys_0[] = { &s_shift, &s_a };
Row_uC row_0(0, readPins, READ_PIN_COUNT, ptrsKeys_0);

Key* ptrsKeys_1[] = { &s_b, &s_c  };
Row_uC row_1(1, readPins, READ_PIN_COUNT, ptrsKeys_1);

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
