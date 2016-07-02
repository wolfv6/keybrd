#ifndef ROW_SHIFTREGISTERS_H
#define ROW_SHIFTREGISTERS_H

#include <RowBase.h>
#include <RowScanner_SPIShiftRegisters.h>
#include <Debouncer_4Samples.h>
//#include <Debouncer_Not.h>

/* Row_DH_IOE is a row connected to an Input/Output Expander.

Instantiation
-------------
Definition of DELAY_MICROSECONDS is explained in RowBase.cpp.
Example instantiation of a row:

    const unsigned int RowBase::DELAY_MICROSECONDS = 1000;

    todo

    Key* const ptrsKeys_0[] = { &k_00, &k_01, &k_02, &k_03, &k_04, &k_05 };
    Row_ShiftRegisters row_0(uint8_t BYTE_COUNT, ptrsKeys_0);

Number of pins in colPort0 should equal number of keys in ptrsKeys_0[] array.
    if a pin is missing, a key will be unresposive
    if a Key pointer is missing, the keyboard will fail in an unprdictable way
*/
class Row_ShiftRegisters : public RowBase
{
    private:
        RowScanner_SPIShiftRegisters scanner;
        Debouncer_4Samples debouncer;
        //Debouncer_Not debouncer; //tested
    public:
        Row_ShiftRegisters(const uint8_t STROBE_PIN, Key *const ptrsKeys[], uint8_t KEY_COUNT)
            : RowBase(ptrsKeys), scanner(STROBE_PIN, KEY_COUNT) { }
        void begin();
        read_pins_t scan(read_pins_mask_t& rowEnd);
        read_pins_t debounce(const read_pins_t rowState, read_pins_t& debounced);
};
#endif
