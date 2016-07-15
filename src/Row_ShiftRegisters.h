#ifndef ROW_SHIFTREGISTERS_H
#define ROW_SHIFTREGISTERS_H

#include <Row.h>
#include <Scanner_ShiftRegs74HC165.h>
#include <Debouncer_Samples.h>

/* Row_ShiftRegisters is a row connected to shift registers.

Instantiation
-------------
Scanner_ShiftRegs74HC165.h has instructions for hardware and setting active state.
Example instantiation of a Row_ShiftRegisters:

    const uint8_t Scanner_ShiftRegs74HC165::SHIFT_LOAD = 10;
    const bool Scanner_ShiftRegs74HC165::STROBE_ON = LOW;    //active low
    const bool Scanner_ShiftRegs74HC165::STROBE_OFF = HIGH;

    Key* const ptrsKeys_0[] = { &k_00, &k_01, &k_02, &k_03, &k_04, &k_05 };
    uint8_t readPinCount_0 = sizeof(ptrsKeys_0)/sizeof(*ptrsKeys_0);
    Row_ShiftRegisters row_0(1, readPinCount_0, ptrsKeys_0);

call begin() from sketch setup():
    void setup()
    {
        Keyboard.begin();
        SPI.begin();
        row_0.begin();
    }

readPinCount should equal number of keys in ptrsKeys_0[] array.
    if readPinCount is too small, a key will be unresponsive
    if readPinCount is too large, the keyboard will fail in an unpredictable way
*/
class Row_ShiftRegisters : public Row
{
    private:
        Scanner_ShiftRegs74HC165 scanner;
        Debouncer_Samples debouncer;
        const uint8_t readPinCount;           //number of read pins
    public:
        Row_ShiftRegisters(const uint8_t strobePin, const uint8_t readPinCount, Key *const ptrsKeys[])
            : Row(ptrsKeys), scanner(strobePin, readPinCount), readPinCount(readPinCount) { }
        void begin();
        void process();
};
#endif
