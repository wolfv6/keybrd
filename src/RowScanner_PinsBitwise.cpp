#include "RowScanner_PinsBitwise.h"
/*
Strobes the row and reads the columns.
Sets rowEnd and returns rowState.
*/
ColPort* const RowScanner_PinsBitwise::scan()
{
    //strobe row on
    if (activeHigh)
    {
        refRowPort.setActivePinHigh(strobePin);
    }
    else //activeLow
    {
        refRowPort.setActivePinLow(strobePin);
    }
    delayMicroseconds(3);                       //time to stablize voltage

    //read the port pins
    refColPort.read();

    //strobe row off
    if (activeHigh)
    {
        refRowPort.setActivePinLow(strobePin);
    }
    else //activeLow
    {
        refRowPort.setActivePinHigh(strobePin);
    }
   
//    return getRowState(refColPort, rowEnd);
    return &refColPort;
}
