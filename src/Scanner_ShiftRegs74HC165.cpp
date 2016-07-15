#include "Scanner_ShiftRegs74HC165.h"

//constructor
Scanner_ShiftRegs74HC165::Scanner_ShiftRegs74HC165(const uint8_t strobePin, uint8_t readPinCount)
    : strobePin(strobePin), byte_count(ceil (float(readPinCount)/8))
{
    //configure controller to communicate with shift register matrix
    pinMode(strobePin, OUTPUT);
    pinMode(SHIFT_LOAD, OUTPUT);
}

void Scanner_ShiftRegs74HC165::begin()
{
    //initialize shift register's shift/load pin
    digitalWrite(SHIFT_LOAD, HIGH);
}

/* scan() strobes the row's strobePin and retuns state of the shift register's input pins.
Bitwise variables are 1 bit per key.
*/
read_pins_t Scanner_ShiftRegs74HC165::scan()
{
    read_pins_t readState = 0;                  //bitwise, 1 means key is pressed, 0 means released

    //strobe row on
    digitalWrite(strobePin, STROBE_ON);
    delayMicroseconds(3);                       //time to stablize voltage

    //read all the column pins
    digitalWrite(SHIFT_LOAD, LOW);              //load parallel inputs to the register
    digitalWrite(SHIFT_LOAD, HIGH);             //shift the data toward a serial output
    SPI.transfer(&readState, byte_count);

    //strobe row off
    digitalWrite(strobePin, STROBE_OFF);

    //for testing on breadboard, clear unpowered pins
    readState &= 0b11110001000100010001000100010001; //todo delete this line

    return readState;
}

