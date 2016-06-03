/* debounce() sets debounced and returns debouncedChanged.  All variables are bitwise.
For parameter, 1 means pressed, 0 means released.
For return, 1 means debounced changed.
*/
#include "Row.h"

uint8_t Row::debounce(const uint8_t rowState)
{
    return debouncer.debounce(rowState, debounced);
}
