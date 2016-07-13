#include "Scanner_Port.h"
/*
Strobes the row and reads the columns.
*/
uint8_t Scanner_Port::scan()
{
    uint8_t readState;

    /*if (STROBE_ON == LOW)                       //if activeLow
    {
        refStrobePort.setActivePinLow(strobePin);
    }
    else                                        //if activeHigh
    {
        refStrobePort.setActivePinHigh(strobePin);
    }*/
    //strobe row on
    refStrobePort.write(STROBE_PIN, STROBE_ON);
    delayMicroseconds(3);                       //time to stablize voltage

    //read the port pins
    readState = refReadPort.read();

    //strobe row off
    refStrobePort.write(STROBE_PIN, STROBE_OFF);
    /*if (STROBE_ON == LOW)                       //if activeLow
    {
        refStrobePort.setActivePinHigh(strobePin);
    }
    else                                        //if activeHigh
    {
        refStrobePort.setActivePinLow(strobePin);
    }*/
   
    //return refReadPort.getPortState();
    return readState;
}
