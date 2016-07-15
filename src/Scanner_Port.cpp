#include "Scanner_Port.h"

/* scan() strobes the row's strobePin and retuns state of port's input pins.
Bitwise variables are 1 bit per key.
*/
uint8_t Scanner_Port::scan()
{
    uint8_t readState;                          //bitwise, 1 means key is pressed, 0 means released

    //strobe on
    refPortWrite.write(strobePin, STROBE_ON);
    delayMicroseconds(3);                       //time to stabilize voltage

    //read the port pins
    readState = refPortRead.read();

    //strobe off
    refPortWrite.write(strobePin, STROBE_OFF);
   
    return readState;
}
