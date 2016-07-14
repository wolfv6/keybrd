#include "Scanner_Port.h"

/* scan() strobes the row's STROBE_PIN and retuns state of port's input pins.
Bitwise variables are 1 bit per key.
*/
uint8_t Scanner_Port::scan()
{
    uint8_t readState;                          //bitwise, 1 means key is pressed, 0 means released

    //strobe on
    refPortWrite.write(STROBE_PIN, STROBE_ON);
    delayMicroseconds(3);                       //time to stablize voltage

    //read the port pins
    readState = refPortRead.read();

    //strobe off
    refPortWrite.write(STROBE_PIN, STROBE_OFF);
   
    return readState;
}
