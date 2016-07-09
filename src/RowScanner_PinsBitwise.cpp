#include "RowScanner_PinsBitwise.h"
/*
Strobes the row and reads the columns.
*/
ColPort* const RowScanner_PinsBitwise::scan()
{
    //strobe row on
    if (STROBE_ON == LOW)
    {
        refRowPort.setActivePinLow(strobePin);
    }
    else //activeLow
    {
        refRowPort.setActivePinHigh(strobePin);
    }
    delayMicroseconds(3);                       //time to stablize voltage

    //read the port pins
    refColPort.read();

    //strobe row off
    if (STROBE_ON == LOW)
    {
        refRowPort.setActivePinHigh(strobePin);
    }
    else //activeLow
    {
        refRowPort.setActivePinLow(strobePin);
    }
   
    return &refColPort;
}
