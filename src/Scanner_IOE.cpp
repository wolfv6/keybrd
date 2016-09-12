#include "Scanner_IOE.h"

/* init() is called once for each row from Row constructor.
*/
void Scanner_IOE::init(const uint8_t strobePin)
{
    //empty
}

/* begin() should be called once from sketch setup().
Initiates communication protocal and configs ports.
*/
void Scanner_IOE::begin()
{
    refPortWrite.begin();
    refPortRead.begin(strobeOn);
}

/* scan() is called on every iteration of sketch loop().
scan() strobes the row's strobePin and retuns state of port's input pins.
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

    if (strobeOn == LOW)                        //if active low
    {
        readState = ~readState;
    }
    return readState;
}
