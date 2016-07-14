#include "Scanner_Port.h"
/*
Strobes the row and reads the columns.
*/
uint8_t Scanner_Port::scan()
{
    uint8_t readState;

    //strobe row on
    refPortWrite.write(STROBE_PIN, STROBE_ON);
    delayMicroseconds(3);                       //time to stablize voltage

    //read the port pins
    readState = refPortRead.read();

    //strobe row off
    refPortWrite.write(STROBE_PIN, STROBE_OFF);
   
    //return refPortRead.getPortState();
    return readState;
}
