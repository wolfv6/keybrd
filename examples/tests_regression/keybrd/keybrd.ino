/* this works on Teensy LC 1*bb, active low and active high
MCP23018 is not working, MCP23018::begin() hangs, details in setup()

| Layout | **0** | **1** |
|:------:|-------|-------|
|  **0** | a     | b     |
|  **1** | c     | d     |
*/
// ################## GLOBAL ###################
// ================= INCLUDES ==================
#include <Debug.h>

//LEDs
#include <LED_PinNumber.h>
#include "classes/Code_Sc_LED.h"                //symlink: ln -s ../classes classes

//IOE Ports
#include "IOExpanderPort.h"
#include <RowPort_MCP23018.h>
#include <ColPort_MCP23018.h>

//Codes
#include <Code_Sc.h>

//Matrix
#include <Row_uC.h>
#include <SPI.h>
#include <Row_ShiftRegisters.h>

// =============== CONFIGURATION ===============
const unsigned int RowBase::DELAY_MICROSECONDS = 500;

//activeLow  has diode cathode (band) on row
//activeHigh has diode cathode (band) on col, and pull down resistors on cols
//0=active low, 1= active high
const bool RowScanner_PinsArray::activeHigh = 0;
//const bool RowScanner_PinsBitwise::activeHigh = 0;

Debug debug;

// ================ LEFT PORTS =================
uint8_t readPins[] = {14, 15};
uint8_t READ_PIN_COUNT = sizeof(readPins)/sizeof(*readPins);

LED_PinNumber LED1(16);                     //Teensy LC pins 16, 17 are 20 ma

// ================ RIGHT PORTS ================
/*
const uint8_t IOExpanderPort::ADDR = 0x20;

IOExpanderPort portA(0, 0);
RowPort_MCP23018 rowPort(portA);

IOExpanderPort portB(1, 0);
ColPort_MCP23018 colPort(portB, 1<<0 | 1<<1 );
*/
// =================== CODES ===================
Code_Sc s_a(KEY_A);
Code_Sc s_b(KEY_B);
Code_Sc s_c(KEY_C);
Code_Sc_LED s_d(KEY_D, LED1);

Code_Sc s_0(KEY_0);
Code_Sc s_1(KEY_1);
Code_Sc s_2(KEY_2);
Code_Sc s_3(KEY_3);
Code_Sc s_4(KEY_4);
Code_Sc s_5(KEY_5);
Code_Sc s_6(KEY_6);
Code_Sc s_7(KEY_7);
Code_Sc s_z(KEY_Z);

// ================= LEFT ROWS =================
Key* ptrsKeys_L0[] = { &s_a, &s_b };
Row_uC row_L0(0, readPins, READ_PIN_COUNT, ptrsKeys_L0);

Key* ptrsKeys_L1[] = { &s_c, &s_d };
Row_uC row_L1(1, readPins, READ_PIN_COUNT, ptrsKeys_L1);

// ================= RIGHT ROWS ================
/*
Key* ptrsKeys_R[] = { &s_0, &s_z, &s_z, &s_z,
                      &s_4, &s_z, &s_z, &s_z,
                      &s_8, &s_z, &s_z, &s_z }; //the s_z are place holders and should not print
*/
Key* ptrsKeys_R[] = { &s_0, &s_1, &s_2, &s_3,
                      &s_4, &s_5, &s_6, &s_7 }; //the most that 8-bit send() can handle
const uint8_t KEY_COUNT = sizeof(ptrsKeys_R)/sizeof(*ptrsKeys_R);
//Row_ShiftRegisters row_R(9, 2, ptrsKeys_R, KEY_COUNT);
Row_ShiftRegisters row_R(9, 1, ptrsKeys_R, KEY_COUNT); //1 byte

// ################### MAIN ####################
void setup()
{
    Keyboard.begin();
    SPI.begin();
    row_R.begin();

    //delay(1000);        //time for OS to detect USB before printing
    Keyboard.print(F("activeState.ino "));
    debug.print_free_RAM();

    //Wire.begin();
/* Teensy LC on 1*bb 6/13/16 copied to: activeState_MCP23018_begin_hangs.no
RowPort_MCP23018::begin() hangs
ColPort_MCP23018::begin() sometimes hangs, sometimes prints after 6 seconds
PCA9655E::begin()s works on 4*bb
maybe hangs if IOE is not attached because endTransmission() waiting for confirmation??

trouble shooting MCP23018::begin()s
    checked wiring against datasheets
    measured power and ground, 3.3 volts checks out
!! next things to check could take days:
    test MCP23018 with Teensy 2.0, because it worked last year
    set Teensy 2.0 to 3.3 volts and test again
    try with PCA9655E instead of MCP23018 (works on 4*bb)
    might be solder joints on LC (I soldered it), try using other Teensy LC
    test MCP23018 on simple demo sketch /home/wolfv/Documents/Arduino/demo_keep/mcp23018_../
    test MCP23018 with signal analyzer

    //rowPort.begin(); //this breaks sketch, does not print "activeState.ino ", kb unresponsive
    //colPort.begin(RowScanner_PinsBitwise::activeHigh); //hanges for 6 seconds
    Keyboard.println(F("  after Port.begin()"));
*/
}

//uint16_t next = 0;
//elapsedMillis elapsed;

void loop()
{
    row_L0.process();
    row_L1.process();

    row_R.process();

    //row_R0.process();
    //row_R1.process();

/* used this when debugging MCP23018::begin() hangs
if ( (next < 10) && (elapsed > 1000 * next) )
{
    Keyboard.print(next);
    Keyboard.print(F(" "));
    next++;
}
*/
//delay(100);
//Keyboard.println("");
}
