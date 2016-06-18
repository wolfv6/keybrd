#include "RowScanner_SPIShiftRegisters.h"

void RowScanner_SPIShiftRegisters::begin()
{
    pinMode (SS, OUTPUT);
    digitalWrite (SS, HIGH);
}

/*
Sets rowEnd and returns rowState.
*/
uint8_t RowScanner_SPIShiftRegisters::scan(uint16_t& rowEnd)
{
//todo rowEnd, rowState, return int size depend on BYTE_COUNT, like in send()
    uint8_t rowState;

    digitalWrite(SS, LOW);
    digitalWrite(SS, HIGH);
    SPI.transfer(&rowState, BYTE_COUNT);
    rowEnd = 1 << KEY_COUNT;
    return rowState;
}

