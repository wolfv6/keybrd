#include "Row_uC.h"

/*
process() scans the row and calls any newly pressed or released keys.
*/
void Row_uC::process()
{
    //these variables are all bitwise, one bit per key
    read_pins_t rowState;                       //1 means pressed, 0 means released
    uint8_t keyCount;
    read_pins_t debouncedChanged;               //1 means debounced changed

    rowState = scanner.scan(keyCount);
/*
Keyboard.print(" keyCount=");
Keyboard.print(keyCount);
Keyboard.print(" rowState=");
Keyboard.print(rowState);
*/
    debouncedChanged = debouncer.debounce(rowState, debounced);
/*
Keyboard.print(" debounced=");
Keyboard.print(debounced);
*/
    pressRelease(keyCount, debouncedChanged);
}
