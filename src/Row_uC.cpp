#include "Row_uC.h"

/*
process() scans the row and calls any newly pressed or released keys.
*/
void Row_uC::process()
{
    //these variables are all bitwise, one bit per key
    read_pins_t rowState;                       //1 means pressed, 0 means released
    //uint8_t readPinCount;
    read_pins_t debouncedChanged;               //1 means debounced changed

    rowState = scanner.scan();
    debouncedChanged = debouncer.debounce(rowState, debounced);
    pressRelease(READ_PIN_COUNT, debouncedChanged);
}
