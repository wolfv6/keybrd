/* keybrd_1_breadboard.ino

| Layout | **0** | **1** |
|:------:|-------|-------|
|  **0** | 1     | a     |
|  **1** | b     | c     |
*/
// ################## GLOBAL ###################
// ================= INCLUDES ==================
#include <ScanDelay.h>
#include <Code_Sc.h>
#include <Row_uC.h>

// ============ SPEED CONFIGURATION ============
ScanDelay scanDelay(9000);

// ================ ACTIVE STATE ===============
const bool Scanner_uC::STROBE_ON = LOW;
const bool Scanner_uC::STROBE_OFF = HIGH;

// =================== PINS ====================
uint8_t readPins[] = {14, 15};
uint8_t READ_PIN_COUNT = sizeof(readPins)/sizeof(*readPins);

// =================== CODES ===================
Code_Sc s_1(KEY_1);
Code_Sc s_a(KEY_A);
Code_Sc s_b(KEY_B);
Code_Sc s_c(KEY_C);

// =================== ROWS ====================
Key* ptrsKeys_0[] = { &s_1, &s_a };
Row_uC row_0(0, readPins, READ_PIN_COUNT, ptrsKeys_0);

Key* ptrsKeys_1[] = { &s_b, &s_c };
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
