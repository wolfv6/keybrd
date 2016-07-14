#ifndef ROW_SHIFTREGISTERS_H
#define ROW_SHIFTREGISTERS_H

#include <Row.h>
#include <Scanner_ShiftRegs74HC165.h>
#include <Debouncer_Samples.h>
//#include <Debouncer_Not.h>

/* Row_DH_IOE is a row connected to an Input/Output Expander.

Instantiation
-------------
Definition of DELAY_MICROSECONDS is explained in Row.cpp.
Example instantiation of a row:

    const unsigned int Row::DELAY_MICROSECONDS = 1000;

    todo

    Key* const ptrsKeys_0[] = { &k_00, &k_01, &k_02, &k_03, &k_04, &k_05 };
    Row_ShiftRegisters row_0(uint8_t BYTE_COUNT, ptrsKeys_0);

Number of pins in colPort0 should equal number of keys in ptrsKeys_0[] array.
    if a pin is missing, a key will be unresposive
    if a Key pointer is missing, the keyboard will fail in an unprdictable way
*/
class Row_ShiftRegisters : public Row
{
    private:
        Scanner_ShiftRegs74HC165 scanner;
        Debouncer_Samples debouncer;
        //Debouncer_Not debouncer; //passed test
        const uint8_t READ_PIN_COUNT;           //number of read pins
    public:
        Row_ShiftRegisters(const uint8_t STROBE_PIN, uint8_t READ_PIN_COUNT, Key *const ptrsKeys[])
            : Row(ptrsKeys), scanner(STROBE_PIN, READ_PIN_COUNT), READ_PIN_COUNT(READ_PIN_COUNT) { }
        void begin();
        void process();
};
#endif
