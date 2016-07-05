#include "Row_uC.h"

/*
process() scans the row and calls any newly pressed or released keys.
*/
void Row_uC::process()
{
    //these variables are all bitwise, one bit per key
    read_pins_t rowState;                       //1 means pressed, 0 means released
    read_pins_mask_t rowEnd;                    //1 bit marks positioned after last key of row
    read_pins_t debouncedChanged;               //1 means debounced changed

    rowState = scanner.scan(rowEnd);
    debouncedChanged = debouncer.debounce(rowState, debounced);
    pressRelease(rowEnd, debouncedChanged);
}
