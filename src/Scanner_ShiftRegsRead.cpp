#include "Scanner_ShiftRegsRead.h"

/* constructor
Parameter activeState is not used.
*/
Scanner_ShiftRegsRead::Scanner_ShiftRegsRead(const bool activeState,
        const uint8_t slaveSelect, const uint8_t byte_count)
    : slaveSelect(slaveSelect), byte_count(byte_count)
{
    pinMode(slaveSelect, OUTPUT);
}

/* init() is called once for each row from Row constructor.
*/
void Scanner_ShiftRegsRead::init(const uint8_t strobePin)
{
    //empty function
}

/* begin() should be called once from sketch setup().
Initializes shift register's shift/load pin.
*/
void Scanner_ShiftRegsRead::begin()
{
    SPI.begin();
    digitalWrite(slaveSelect, HIGH);
}

/* scan() returns state of the shift register's input pins.
Parameter strobePin is not used.
No strobe pin is needed, the shift register is wired so the strobe is effectivley always "on".
Bit patterns are 1 bit per key.
*/
read_pins_t Scanner_ShiftRegsRead::scan(const uint8_t strobePin)
{
    read_pins_t readState = 0;                  //bits, 1 means key is pressed, 0 means released

    //read all the column pins
    digitalWrite(slaveSelect, HIGH);            //shift the data toward a serial output
    SPI.transfer(&readState, byte_count);
    digitalWrite(slaveSelect, LOW);             //load parallel inputs to the register

    return readState;
}

