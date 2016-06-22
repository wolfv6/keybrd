#include "RowScanner_SPIShiftRegisters.h"

void RowScanner_SPIShiftRegisters::begin()
{
    pinMode (SS, OUTPUT);
    digitalWrite (SS, HIGH);
}

/*
Sets rowEnd and returns rowState.
*/
read_pins_t RowScanner_SPIShiftRegisters::scan(read_pins_mask_t& rowEnd)
{
//todo rowEnd, rowState, return int size depend on BYTE_COUNT, like in send()
    read_pins_t rowState = 0;

    digitalWrite(SS, LOW);
    digitalWrite(SS, HIGH);
    SPI.transfer(&rowState, BYTE_COUNT);
    rowEnd = 1 << KEY_COUNT;
    return rowState;
}

