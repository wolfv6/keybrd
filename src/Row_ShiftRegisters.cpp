#include "Row_ShiftRegisters.h"

void Row_ShiftRegisters::begin()
{
    scanner.begin();
}

read_pins_t Row_ShiftRegisters::scan(read_pins_mask_t& rowEnd)
{
    return scanner.scan(rowEnd);
}

read_pins_t Row_ShiftRegisters::debounce(const read_pins_t rowState, read_pins_t& debounced)
{
    return debouncer.debounce(rowState, debounced);
}
