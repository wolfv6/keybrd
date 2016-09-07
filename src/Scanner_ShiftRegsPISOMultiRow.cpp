#include "Scanner_ShiftRegsPISOMultiRow.h"

/* constructor
*/
Scanner_ShiftRegsPISOMultiRow::Scanner_ShiftRegsPISOMultiRow(const bool strobeOn,
        const uint8_t slaveSelect, const uint8_t byte_count)
    : strobeOn(strobeOn), strobeOff(!strobeOn),
        slaveSelect(slaveSelect), byte_count(byte_count)
{
    pinMode(slaveSelect, OUTPUT);
}

/* init() is called once for each row from Row constructor.
Configures controller to communicate with shift register matrix.
*/
void Scanner_ShiftRegsPISOMultiRow::init(const uint8_t strobePin)
{
    pinMode(strobePin, OUTPUT);
}

/* begin() should be called once from sketch setup().
Initializes shift register's shift/load pin.
*/
void Scanner_ShiftRegsPISOMultiRow::begin()
{
    digitalWrite(slaveSelect, HIGH);
}

/* scan() strobes the row's strobePin and returns state of the shift register's input pins.
strobePin is Arduino pin number connected to this row.
Bitwise variables are 1 bit per key.
*/
read_pins_t Scanner_ShiftRegsPISOMultiRow::scan(const uint8_t strobePin)
{
    read_pins_t readState = 0;                  //bitwise, 1 means key is pressed, 0 means released

    //strobe row on
    digitalWrite(strobePin, strobeOn);
    delayMicroseconds(3);                       //time to stablize voltage

    //read all the column pins
    digitalWrite(slaveSelect, LOW);              //load parallel inputs to the register
    digitalWrite(slaveSelect, HIGH);             //shift the data toward a serial output
    SPI.transfer(&readState, byte_count);

    //strobe row off
    digitalWrite(strobePin, strobeOff);

    return readState;
}

