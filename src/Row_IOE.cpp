#include "Row_IOE.h"

/*
process() scans the row and calls any newly pressed or released keys.
*/
void Row_IOE::process()
{
    //these variables are all bitwise, one bit per key
    uint8_t rowState;                           //1 means pressed, 0 means released
    uint16_t rowEnd;                            //1 bit marks positioned after last key of row
    uint8_t debouncedChanged;                   //1 means debounced changed

    wait();
    rowState = scanner.scan(rowEnd);
    debouncedChanged = debouncer.debounce(rowState, debounced);
    pressRelease(rowEnd, debouncedChanged);
}
