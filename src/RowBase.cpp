#include "RowBase.h"
/*
pressRelease() calls key's press() or release() function if it was pressed or released.
Both parameters are bitwise.
rowEnd bit marks positioned immediatly after last key of row.
*/
void RowBase::pressRelease(const uint8_t KEY_COUNT, const read_pins_t debouncedChanged)
{
    read_pins_t isFallingEdge;                  //bitwise, 1 means falling edge
    read_pins_t isRisingEdge;                   //bitwise, 1 means rising edge
    read_pins_mask_t rowMask;                   //bitwise, active col bit is 1
    uint8_t col;                                //index for ptrsKeys[col] array

    //bit=1 if last debounced changed from 1 to 0, else bit=0
    isFallingEdge = debouncedChanged & ~debounced;

    //bit=1 if last debounced changed from 0 to 1, else bit=0
    isRisingEdge = debouncedChanged & debounced;

    for (rowMask=1, col=0; col < KEY_COUNT; rowMask<<=1, col++) //for each key in row
    {
        //release before press avoids impossible key sequence
        if (rowMask & isFallingEdge)            //if key was released
        {
            ptrsKeys[col]->release();
        }

        if (rowMask & isRisingEdge)             //if key was pressed
        {
            ptrsKeys[col]->press();
            keyWasPressed();
        }
    }
}
            
void RowBase::keyWasPressed()
{
    //empty in RowBase class.  To unstick sticky keys, override keyWasPressed() in derived class.
}
