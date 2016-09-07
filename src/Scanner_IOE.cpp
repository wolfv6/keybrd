#include "Scanner_IOE.h"

/* Row constructor calls every Scanner's init().
*/
void Scanner_IOE::init(const uint8_t strobePin)
{
    //emty function
}

/* begin() should be called once from sketch setup().
*/
void Scanner_IOE::begin()
{
    Wire.begin();
    refPortWrite.begin();
    refPortRead.begin();
}

/* scan() strobes the row's strobePin and retuns state of port's input pins.
Bitwise variables are 1 bit per key.
*/
read_pins_t Scanner_IOE::scan(const uint8_t strobePin)
{
    uint8_t readState;                          //bitwise, 1 means key is pressed, 0 means released

    //strobe on
    refPortWrite.write(strobePin, strobeOn);
    delayMicroseconds(3);                       //time to stabilize voltage

    //read the port pins
    readState = refPortRead.read();

    //strobe off
    refPortWrite.write(strobePin, strobeOff);

    return readState;
}
