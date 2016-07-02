#include "RowScanner_SPIShiftRegisters.h"

void RowScanner_SPIShiftRegisters::begin()
{
    //configure row
    pinMode(STROBE_PIN, OUTPUT);

    //initialize shift register's shift/load pin
    pinMode(SHIFT_LOAD, OUTPUT);
    digitalWrite(SHIFT_LOAD, HIGH);
}

/*
Sets rowEnd and returns rowState.
*/
read_pins_t RowScanner_SPIShiftRegisters::scan(read_pins_mask_t& rowEnd)
{
    read_pins_t rowState = 0;

    //strobe row on
    digitalWrite(STROBE_PIN, HIGH);
    delayMicroseconds(3);                       //time to stablize voltage

    //read all the column pins
    digitalWrite(SHIFT_LOAD, LOW);              //load parallel inputs to the register
    digitalWrite(SHIFT_LOAD, HIGH);             //shift the data toward a serial output
    SPI.transfer(&rowState, BYTE_COUNT);

    //strobe row off
    digitalWrite(STROBE_PIN, LOW);

    rowEnd = 1 << KEY_COUNT;

    //clear unpowered pins (for testing bb) todo
    if (BYTE_COUNT == 1) rowState &=                         0b00010001;
    if (BYTE_COUNT == 2) rowState &=                 0b0001000100010001;
    if (BYTE_COUNT == 3) rowState &=         0b000100010001000100010001;
    if (BYTE_COUNT == 4) rowState &= 0b01010001000100010001000100010001; //also 31st key

//Keyboard.print(" ");//todo
//Keyboard.print(rowState); //why does rowState change to 1 for both rows? (row pin 8 is unplugged)
    return rowState;
}

