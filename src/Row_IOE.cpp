#include "Row_IOE.h"

uint8_t Row_IOE::scan(uint16_t& rowEnd)
{
    return scanner.scan(rowEnd);
}

uint8_t Row_IOE::debounce(const uint8_t rowState, uint8_t& debounced)
{
    return debouncer.debounce(rowState, debounced);
}
