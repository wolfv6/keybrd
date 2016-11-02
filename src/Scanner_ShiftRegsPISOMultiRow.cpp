#include "Scanner_ShiftRegsPISOMultiRow.h"

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
    digitalWrite(slaveSelect, HIGH);            //initialize ??only needed for first scan
    SPI.begin(); //todo move this to constructor or init()
}

/* scan() strobes the row's strobePin and returns state of the shift register's input pins.
strobePin is Arduino pin number connected to this row.
Bit patterns are 1 bit per key.

Scanner_ShiftRegsPISOMultiRow class was tested on two sets of 74HC165 shift registers
and 74AHC1G126 tri-state buffer chips

74HC165 is not an SPI device.
The 74HC165 SH/LD polarity is the inverse of SPI slave-select convention.
Most SPI chips will high-Z their MISO pin when their slave select signal is high.
To use SPI-like protocol, 74HC*126 will high-Z the MISO pin when the slave select signal is low.

SPI.beginTransaction() and SPI.endTransaction() are not needed,
but would be needed if trackball uses interrupts.
*/
read_pins_t Scanner_ShiftRegsPISOMultiRow::scan(const uint8_t strobePin)
{
    read_pins_t readState = 0;                  //bits, 1 means key is pressed, 0 means released

    digitalWrite(strobePin, strobeOn);          //strobe on

    //SPI.beginTransaction( SPISettings(5000000, MSBFIRST, SPI_MODE0) ); //control SPI bus, 5 MHz

    delayMicroseconds(20);                      //photo-transistor at 3.3v needs 20 ms to stablize

    digitalWrite(slaveSelect, HIGH);            //shift the data toward a serial output

    digitalWrite(strobePin, strobeOff);         //strobe off

    SPI.transfer(&readState, byte_count);

    //SPI.endTransaction();

    digitalWrite(slaveSelect, LOW);             //load parallel inputs to registers

    return readState;
}

