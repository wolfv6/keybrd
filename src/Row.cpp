#include "Row.h"
/*
pressRelease() calls key's press() or release() function if it was pressed or released.
Both parameters are bitwise.
*/
void Row::pressRelease(const uint8_t readPinCount, const read_pins_t debouncedChanged)
{
    read_pins_t isFallingEdge;                  //bitwise, 1 means falling edge
    read_pins_t isRisingEdge;                   //bitwise, 1 means rising edge
    read_pins_t readMask;                       //bitwise, active read bit is 1
    uint8_t i;                                  //index for ptrsKeys[i] array

    //bit=1 if last debounced changed from 1 to 0, else bit=0
    isFallingEdge = debouncedChanged & ~debounced;

    //bit=1 if last debounced changed from 0 to 1, else bit=0
    isRisingEdge = debouncedChanged & debounced;

    for (readMask=1, i=0; i < readPinCount; readMask<<=1, i++) //for each key in row
    {
        //release before press avoids impossible key sequence
        if (readMask & isFallingEdge)            //if key was released
        {
            ptrsKeys[i]->release();
        }

        if (readMask & isRisingEdge)             //if key was pressed
        {
            ptrsKeys[i]->press();
            keyWasPressed();
        }
    }
}
            
void Row::keyWasPressed()
{
    //empty in Row class.  To unstick sticky keys, override keyWasPressed() in derived class.
}
