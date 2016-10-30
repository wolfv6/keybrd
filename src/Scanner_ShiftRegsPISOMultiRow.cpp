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
    //digitalWrite(strobePin, strobeOff);//todo is this needed?
}

/* begin() should be called once from sketch setup().
Initializes shift register's shift/load pin.
*/
void Scanner_ShiftRegsPISOMultiRow::begin()
{
    SPI.begin();
}

/* scan() strobes the row's strobePin and returns state of the shift register's input pins.
strobePin is Arduino pin number connected to this row.
Bit patterns are 1 bit per key.
*/
read_pins_t Scanner_ShiftRegsPISOMultiRow::scan(const uint8_t strobePin)
{
    read_pins_t readState = 0;                  //bits, 1 means key is pressed, 0 means released

    //strobe on
    digitalWrite(strobePin, strobeOn);

    //SPI.beginTransaction( SPISettings(5000000, MSBFIRST, SPI_MODE0) ); //control SPI bus, 5 MHz
    //digitalWrite(slaveSelect, LOW);             //assert slave

    delayMicroseconds(3);                       //time to stabilize photo-transistor todo needed?
    delayMicroseconds(50); //todo for sr2_LEDs_strobe.ino

    //read all the column pins
    digitalWrite(slaveSelect, HIGH);            //shift the data toward a serial output

    SPI.transfer(&readState, byte_count);
    digitalWrite(slaveSelect, LOW);             //load parallel inputs to registers

    //digitalWrite(slaveSelect, HIGH);            //de-assert slave
    //SPI.endTransaction();

    //strobe off
    digitalWrite(strobePin, strobeOff);

    return readState;
}

