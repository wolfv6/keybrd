#include "Row_ShiftRegisters.h"

void Row_ShiftRegisters::begin()
{
    scanner.begin();
}

uint8_t Row_ShiftRegisters::scan(uint16_t& rowEnd)
{
    return scanner.scan(rowEnd);
}

uint8_t Row_ShiftRegisters::debounce(const uint8_t rowState, uint8_t& debounced)
{
    return debouncer.debounce(rowState, debounced);
}
