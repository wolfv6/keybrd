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
    refPortWrite.beginProtocol();
    refPortWrite.begin(activeState);
    refPortRead.begin(activeState);
}

/* scan() is called on every iteration of sketch loop().
strobePin is a bit pattern, 1 means that row pin is active.
scan() strobes the row's strobePin and retuns state of port's input pins.
*/
read_pins_t Scanner_IOE::scan(const uint8_t strobePin)
{
    uint8_t readState;                          //bits, 1 means key is pressed, 0 means released

    //strobe on
    if (activeState == LOW)                     //if active low
    {
        refPortWrite.writeLow(strobePin);
    }
    else                                        //if active high
    {
        refPortWrite.writeHigh(strobePin);
    }
    delayMicroseconds(3);                       //time to stabilize voltage

    //read the port pins
    readState = refPortRead.read();

    //strobe off
    if (activeState == LOW)                     //if active low
    {
        refPortWrite.writeHigh(strobePin);
        readState = ~readState;
    }
    else                                        //if active high
    {
        refPortWrite.writeLow(strobePin);
    }

    return readState;
}
