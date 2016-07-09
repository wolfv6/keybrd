#include "Row_ShiftRegisters.h"

void Row_ShiftRegisters::process()
{
    //these variables are all bitwise, one bit per key
    read_pins_t rowState;                       //1 means pressed, 0 means released
    uint8_t keyCount;
    read_pins_t debouncedChanged;               //1 means debounced changed

    rowState = scanner.scan(keyCount);
    debouncedChanged = debouncer.debounce(rowState, debounced);
    pressRelease(keyCount, debouncedChanged);
}

void Row_ShiftRegisters::begin()
{
    scanner.begin();
}
