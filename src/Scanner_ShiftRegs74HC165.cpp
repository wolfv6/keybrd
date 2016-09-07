#include "Scanner_ShiftRegs74HC165.h"

Scanner_ShiftRegs74HC165::Scanner_ShiftRegs74HC165(const bool strobeOn, const uint8_t slaveSelect,
        const uint8_t readPinCount)
    : strobeOn(strobeOn), strobeOff(!strobeOn), slaveSelect(slaveSelect),
        byte_count( ceil(float(readPinCount)/8) )
{
    pinMode(slaveSelect, OUTPUT);
}

/* init() is called once for each row from Row constructor.
Configure controller to communicate with shift register matrix.
*/
void Scanner_ShiftRegs74HC165::init(const uint8_t strobePin)
{
    pinMode(strobePin, OUTPUT);
}

/* begin() should be called once from sketch setup().
*/
void Scanner_ShiftRegs74HC165::begin()
{
    //initialize shift register's shift/load pin
    digitalWrite(slaveSelect, HIGH);
}

/* scan() strobes the row's strobePin and returns state of the shift register's input pins.
strobePin is Arduino pin number connected to this row
Bitwise variables are 1 bit per key.
*/
read_pins_t Scanner_ShiftRegs74HC165::scan(const uint8_t strobePin)
{
    read_pins_t readState = 0;                  //bitwise, 1 means key is pressed, 0 means released

    //strobe row on
    digitalWrite(strobePin, strobeOn);
    //delayMicroseconds(3);                       //time to stablize voltage
    delayMicroseconds(333);                       //todo

    //read all the column pins
    digitalWrite(slaveSelect, LOW);              //load parallel inputs to the register
    digitalWrite(slaveSelect, HIGH);             //shift the data toward a serial output
    //SPI.transfer(&readState, byte_count);
    SPI.transfer(&readState, 4);//todo

    //strobe row off
    digitalWrite(strobePin, strobeOff);

    return readState;
}

