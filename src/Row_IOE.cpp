#include "Row_IOE.h"

read_pins_t Row_IOE::scan(read_pins_mask_t& rowEnd)
{
    return scanner.scan(rowEnd);
}

read_pins_t Row_IOE::debounce(const read_pins_t rowState, read_pins_t& debounced)
{
    return debouncer.debounce(rowState, debounced);
}
