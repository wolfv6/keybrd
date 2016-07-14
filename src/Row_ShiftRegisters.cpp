#include "Row_ShiftRegisters.h"

void Row_ShiftRegisters::process()
{
    //these variables are all bitwise, one bit per key
    read_pins_t readState;                       //1 means pressed, 0 means released
    read_pins_t debouncedChanged;               //1 means debounced changed

    readState = scanner.scan();
    debouncedChanged = debouncer.debounce(readState, debounced);
    send(READ_PIN_COUNT, debouncedChanged);
}

void Row_ShiftRegisters::begin()
{
    scanner.begin();
}
