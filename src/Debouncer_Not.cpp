#include "Debouncer_Not.h"

/* debounce() sets debounced and returns debouncedChanged.
All parameters and variables are bitwise.
For parameters, 1 means pressed, 0 means released.
For return, 1 means debounced changed.
*/
read_pins_t Debouncer_Not::debounce(const read_pins_t rawSignal, read_pins_t& debounced)
{
    read_pins_t previousDebounced;              //bitwise, 1 means pressed, 0 means released

    previousDebounced = debounced;
    debounced = rawSignal;
    return debounced xor previousDebounced;
}

