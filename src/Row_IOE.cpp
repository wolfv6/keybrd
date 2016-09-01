#include "Row_IOE.h"

void Row_IOE::process()
{
    //these variables are all bitwise, one bit per key
    uint8_t readState;                          //1 means pressed, 0 means released
    uint8_t debouncedChanged;                   //1 means debounced changed

    readState = scanner.scan();
    debouncedChanged = debouncer.debounce(readState, debounced);
    send(readPinCount, debouncedChanged);
}
