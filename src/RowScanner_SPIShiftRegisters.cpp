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
//todo rowEnd, rowState, return int size depend on BYTE_COUNT, like in send(), set in config_keybrd?
    read_pins_t rowState = 0;

    digitalWrite(SS, LOW);                      //load parallel inputs to the register
    digitalWrite(SS, HIGH);                     //shift the data toward a serial output
    SPI.transfer(&rowState, BYTE_COUNT);
    rowEnd = 1 << KEY_COUNT;
    return rowState;
}

