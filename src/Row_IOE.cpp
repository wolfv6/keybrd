#include "Row_IOE.h"

void Row_IOE::process()
{
    //these variables are all bitwise, one bit per key
    uint8_t rowState;                       //1 means pressed, 0 means released
    //read_pins_mask_t rowEnd;                    //1 bit marks positioned after last key of row
    uint8_t debouncedChanged;               //1 means debounced changed
    ColPort* ptrColPort; //new
    uint8_t KEY_COUNT; //new

    ptrColPort = scanner.scan();
    rowState = getRowState(ptrColPort, KEY_COUNT); //new
    debouncedChanged = debouncer.debounce(rowState, debounced);
    pressRelease(KEY_COUNT, debouncedChanged);
}

/*
Copies column pins to rowState.  Unused column pins are not copied.
Sets rowEnd and returns rowState.
rowEnd is a bitwise row mask, one col per bit, where active col bit is 1.
At end of function, 1 bit marks place immediatly after last key of row.
rowEnd is a larger type than portMask so that it can not overflow.
*/
uint8_t Row_IOE::getRowState(ColPort* ptrColPort, uint8_t& KEY_COUNT)
{
    uint8_t rowState = 0;           //bitwise, one key per bit, 1 means key is pressed
    uint8_t portMask;               //bitwise, 1 bit is a colPortState position
    uint8_t rowEnd;                    //1 bit marks positioned after last key of row todo rename

    KEY_COUNT = 0;

    //bitwise colPins, 1 means pin is connected to column
    uint8_t colPins = ptrColPort->getColPins();

    //bitwise colPortState, pin values where set in ColPort::read(), get them now
    uint8_t colPortState = ptrColPort->getPortState();

    /*if (activeHigh) //'activeHigh' was not declared in this scope
    {
        colPortState = ~colPortState; //todo configure IOE polarity to take care of this
    }*/

    for ( portMask = 1; portMask > 0; portMask <<= 1 ) //shift portMask until overflow
    {                                       //for each pin of col port
        if (portMask & colPins)             //if pin is connected to column
        {
            if (portMask & ~colPortState)   //if pin detected a key press
            {
                rowState |= rowEnd;         //set rowState bit for that key
            }

            rowEnd <<= 1;                   //shift rowEnd to next key
            KEY_COUNT++;
        }
    }

    return rowState;
}
