#include "Scanner_ShiftRegsPISOSingleRow.h"

/* constructor
*/
Scanner_ShiftRegsPISOSingleRow::Scanner_ShiftRegsPISOSingleRow(const bool strobeOn,
        const uint8_t slaveSelect, const uint8_t byte_count)
    : slaveSelect(slaveSelect), byte_count(byte_count)
{
    pinMode(slaveSelect, OUTPUT);
}

/* init() is called once for each row from Row constructor.
*/
void Scanner_ShiftRegsPISOSingleRow::init(const uint8_t strobePin)
{
    //empty function
}

/* begin() should be called once from sketch setup().
Initializes shift register's shift/load pin.
*/
void Scanner_ShiftRegsPISOSingleRow::begin()
{
    digitalWrite(slaveSelect, HIGH);
}

/* scan() returns state of the shift register's input pins.
No strobe pin is needed, the shift register is wired so the strobe is effectivley always "on".
Bitwise variables are 1 bit per key.
*/
read_pins_t Scanner_ShiftRegsPISOSingleRow::scan(const uint8_t strobePin)
{
    read_pins_t readState = 0;                  //bitwise, 1 means key is pressed, 0 means released

    //read all the column pins
    digitalWrite(slaveSelect, LOW);              //load parallel inputs to the register
    digitalWrite(slaveSelect, HIGH);             //shift the data toward a serial output
    SPI.transfer(&readState, byte_count);

    return readState;
}

