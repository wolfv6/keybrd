#include "Scanner_ShiftRegs74HC165.h"

//constructor
Scanner_ShiftRegs74HC165::Scanner_ShiftRegs74HC165(const uint8_t STROBE_PIN, uint8_t READ_PIN_COUNT)
    : STROBE_PIN(STROBE_PIN), BYTE_COUNT(ceil (float(READ_PIN_COUNT)/8))
{
    //configure controller to communicate with shift register matrix
    pinMode(STROBE_PIN, OUTPUT);
    pinMode(SHIFT_LOAD, OUTPUT);
}

void Scanner_ShiftRegs74HC165::begin()
{
    //initialize shift register's shift/load pin
    digitalWrite(SHIFT_LOAD, HIGH);
}

/*
returns readState.
*/
read_pins_t Scanner_ShiftRegs74HC165::scan()
{
    read_pins_t readState = 0;

    //strobe row on
    digitalWrite(STROBE_PIN, STROBE_ON);
    delayMicroseconds(3);                       //time to stablize voltage

    //read all the column pins
    digitalWrite(SHIFT_LOAD, LOW);              //load parallel inputs to the register
    digitalWrite(SHIFT_LOAD, HIGH);             //shift the data toward a serial output
    SPI.transfer(&readState, BYTE_COUNT);

    //strobe row off
    digitalWrite(STROBE_PIN, STROBE_OFF);

    //for testing on breadboard, clear unpowered pins
    readState &= 0b11110001000100010001000100010001; //todo

    return readState;
}

