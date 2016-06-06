/* debounce() sets debounced and returns debouncedChanged.  All variables are bitwise.
For parameter, 1 means pressed, 0 means released.
For return, 1 means debounced changed.
*/
#include "Row.h"

/*
process() scans the row and calls any newly pressed or released keys.
*/
void Row::process(const bool activeHigh)
{
    //these variables are all bitwise, one bit per key
    uint8_t rowState;                           //1 means pressed, 0 means released
    uint16_t rowEnd;                            //1 bit marks positioned after last key of row
    uint8_t debouncedChanged;                   //1 means debounced changed

    wait();
    //rowState = scanner.scan(rowEnd, activeHigh);
    debouncedChanged = debouncer.debounce(rowState, debounced);
    pressRelease(rowEnd, debouncedChanged);
}
