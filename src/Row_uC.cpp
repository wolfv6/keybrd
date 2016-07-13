#include "Row_uC.h"

/*
process() scans the row and calls any newly pressed or released keys.
*/
void Row_uC::process()
{
    //these variables are all bitwise, one bit per key
    read_pins_t readState;                       //1 means pressed, 0 means released
    read_pins_t debouncedChanged;               //1 means debounced changed

    readState = scanner.scan();
    debouncedChanged = debouncer.debounce(readState, debounced);
    pressRelease(READ_PIN_COUNT, debouncedChanged);
}
