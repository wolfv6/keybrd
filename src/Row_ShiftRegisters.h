#ifndef ROW_SHIFTREGISTERS_H
#define ROW_SHIFTREGISTERS_H

#include <Row.h>
#include <Scanner_ShiftRegs74HC165.h>
#include <Debouncer_Samples.h>

/* Row_ShiftRegisters is a row connected to shift registers.

Instantiation
-------------
Definition of DELAY_MICROSECONDS is explained in Row.cpp.
Example instantiation of a Row_ShiftRegisters:

    const uint8_t Scanner_ShiftRegs74HC165::SHIFT_LOAD = 10;
    const bool Scanner_ShiftRegs74HC165::STROBE_ON = LOW;    //logic level of strobe on, active low
    const bool Scanner_ShiftRegs74HC165::STROBE_OFF = HIGH;  //logic level of strobe off

    Key* const ptrsKeys_0[] = { &k_00, &k_01, &k_02, &k_03, &k_04, &k_05 };
    uint8_t READ_PIN_COUNT_0 = sizeof(ptrsKeys_0)/sizeof(*ptrsKeys_0);
    Row_ShiftRegisters row_0(1, READ_PIN_COUNT_0, ptrsKeys_0);

call begin() from sketch setup():
    void setup()
    {
        Keyboard.begin();
        SPI.begin();
        row_0.begin();
    }

READ_PIN_COUNT should equal number of keys in ptrsKeys_0[] array.
    if READ_PIN_COUNT is too small, a key will be unresposive
    if READ_PIN_COUNT is too large, the keyboard will fail in an unpredictable way
*/
class Row_ShiftRegisters : public Row
{
    private:
        Scanner_ShiftRegs74HC165 scanner;
        Debouncer_Samples debouncer;
        const uint8_t READ_PIN_COUNT;           //number of read pins
    public:
        Row_ShiftRegisters(const uint8_t STROBE_PIN, const uint8_t READ_PIN_COUNT, Key *const ptrsKeys[])
            : Row(ptrsKeys), scanner(STROBE_PIN, READ_PIN_COUNT), READ_PIN_COUNT(READ_PIN_COUNT) { }
        void begin();
        void process();
};
#endif
