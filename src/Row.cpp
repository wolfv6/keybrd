#include "Row.h"

/* constructor
*/
Row::Row(ScannerInterface& refScanner, const uint8_t strobePin,
        Key* const ptrsKeys[], const uint8_t readPinCount)
    : refScanner(refScanner), strobePin(strobePin),
    ptrsKeys(ptrsKeys), readPinCount(readPinCount), debounced(0)
{
    refScanner.begin(strobePin);
}

/* process() scans the row and calls any newly pressed or released keys.
Bitwise variables are 1 bit per key.
*/
void Row::process()
{
    read_pins_t readState;                      //bitwise, 1 means key is pressed, 0 means released
    read_pins_t debouncedChanged;               //bitwise, 1 means debounced changed

    readState = refScanner.scan(strobePin);
    debouncedChanged = debouncer.debounce(readState, debounced);
    send(readPinCount, debouncedChanged);
}

/*
send() calls key's press() or release() function if key was pressed or released.
Both parameters are bitwise.
*/
void Row::send(const uint8_t readPinCount, const read_pins_t debouncedChanged)
{
    read_pins_t isFallingEdge;                  //bitwise, 1 means falling edge
    read_pins_t isRisingEdge;                   //bitwise, 1 means rising edge
    read_pins_t readMask;                       //bitwise, active bit is 1
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
    //empty in Row class.  To unstick sticky keys, override keyWasPressed() in derived Row class.
}
