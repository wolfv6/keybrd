#include "Row_uC.h"

/* process() scans the row and calls any newly pressed or released keys.
Bitwise variables are 1 bit per key.
*/
void Row_uC::process()
{
    read_pins_t readState;                      //bitwise, 1 means key is pressed, 0 means released
    read_pins_t debouncedChanged;               //bitwise, 1 means debounced changed

    readState = scanner.scan();
    debouncedChanged = debouncer.debounce(readState, debounced);
    send(readPinCount, debouncedChanged);
}
