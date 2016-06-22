#include "Row_uC.h"

read_pins_t Row_uC::scan(read_pins_mask_t& rowEnd)
{
    return scanner.scan(rowEnd);
}

read_pins_t Row_uC::debounce(const read_pins_t rowState, read_pins_t& debounced)
{
    return debouncer.debounce(rowState, debounced);
}
