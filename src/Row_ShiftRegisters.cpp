#include "Row_ShiftRegisters.h"

void Row_ShiftRegisters::process()
{
    //these variables are all bitwise, one bit per key
    read_pins_t rowState;                       //1 means pressed, 0 means released
    read_pins_mask_t rowEnd;                    //1 bit marks positioned after last key of row
    read_pins_t debouncedChanged;               //1 means debounced changed

    wait();
    rowState = scanner.scan(rowEnd);
    debouncedChanged = debouncer.debounce(rowState, debounced);
    pressRelease(rowEnd, debouncedChanged);
}

void Row_ShiftRegisters::begin()
{
    scanner.begin();
}
