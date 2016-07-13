#include "Scanner_Port.h"
/*
Strobes the row and reads the columns.
*/
uint8_t Scanner_Port::scan()
{
    //strobe row on
    if (STROBE_ON == LOW)                       //if activeLow
    {
        refStrobePort.setActivePinLow(strobePin);
    }
    else                                        //if activeHigh
    {
        refStrobePort.setActivePinHigh(strobePin);
    }
    delayMicroseconds(3);                       //time to stablize voltage

    //read the port pins
    refReadPort.read();

    //strobe row off
    if (STROBE_ON == LOW)                       //if activeLow
    {
        refStrobePort.setActivePinHigh(strobePin);
    }
    else                                        //if activeHigh
    {
        refStrobePort.setActivePinLow(strobePin);
    }
   
    return refReadPort.getPortState();
}
