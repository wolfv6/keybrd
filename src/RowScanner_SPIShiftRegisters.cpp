#include "RowScanner_SPIShiftRegisters.h"

//constructor
RowScanner_SPIShiftRegisters::RowScanner_SPIShiftRegisters(const uint8_t STROBE_PIN, uint8_t KEY_COUNT)
    : STROBE_PIN(STROBE_PIN), BYTE_COUNT(ceil (float(KEY_COUNT)/8)), KEY_COUNT(KEY_COUNT)
{
    //configure controller to communicate with shift register matrix
    pinMode(STROBE_PIN, OUTPUT);
    pinMode(SHIFT_LOAD, OUTPUT);
}

void RowScanner_SPIShiftRegisters::begin()
{
    //initialize shift register's shift/load pin
    digitalWrite(SHIFT_LOAD, HIGH);
}

/*
Sets keyCount and returns rowState.
*/
read_pins_t RowScanner_SPIShiftRegisters::scan(uint8_t& keyCount)
{
    read_pins_t rowState = 0;

    //strobe row on
    digitalWrite(STROBE_PIN, STROBE_ON);
    delayMicroseconds(3);                       //time to stablize voltage

    //read all the column pins
    digitalWrite(SHIFT_LOAD, LOW);              //load parallel inputs to the register
    digitalWrite(SHIFT_LOAD, HIGH);             //shift the data toward a serial output
    SPI.transfer(&rowState, BYTE_COUNT);

    //strobe row off
    digitalWrite(STROBE_PIN, STROBE_OFF);

    keyCount = KEY_COUNT;

    //for testing on breadboard, clear unpowered pins
    rowState &= 0b11110001000100010001000100010001; //todo

    return rowState;
}

