#include "Scanner_Port.h"
/*
Strobes the row and reads the columns.
*/
ReadPort* const Scanner_Port::scan()
{
    //strobe row on
    if (STROBE_ON == LOW)
    {
        refStrobePort.setActivePinLow(strobePin);
    }
    else //activeLow
    {
        refStrobePort.setActivePinHigh(strobePin);
    }
    delayMicroseconds(3);                       //time to stablize voltage

    //read the port pins
    refReadPort.read();

    //strobe row off
    if (STROBE_ON == LOW)
    {
        refStrobePort.setActivePinHigh(strobePin);
    }
    else //activeLow
    {
        refStrobePort.setActivePinLow(strobePin);
    }
   
    return &refReadPort;
}
