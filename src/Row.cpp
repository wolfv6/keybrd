#include "Row.h"

/* constructor
init() is called once for each row, to set scanner's uC strobePin to output.
*/
Row::Row(ScannerInterface& refScanner, const uint8_t strobePin,
        Key* const ptrsKeys[], const uint8_t keyCount)
    : refScanner(refScanner), strobePin(strobePin),
    ptrsKeys(ptrsKeys), keyCount(keyCount), debounced(0)
{
    refScanner.init(strobePin);
}

/* process() scans the row and calls any newly pressed or released keys.
Bit pattern variables are 1 bit per key.
*/
void Row::process()
{
    read_pins_t readState;                      //bits, 1 means key is pressed, 0 means released
    read_pins_t debouncedChanged;               //bits, 1 means debounced changed

    readState = refScanner.scan(strobePin);
    debouncedChanged = debouncer.debounce(readState, debounced);
    send(keyCount, debouncedChanged);
}

/*
send() calls key's press() or release() function if key was pressed or released.
Parameter debouncedChanged is bit a pattern.
*/
void Row::send(const uint8_t keyCount, const read_pins_t debouncedChanged)
{
    read_pins_t isFallingEdge;                  //bits, 1 means falling edge
    read_pins_t isRisingEdge;                   //bits, 1 means rising edge
    read_pins_t readPosition;                   //bits, active bit is 1
    uint8_t i;                                  //index for ptrsKeys[i] array

    //bit=1 if last debounced changed from 1 to 0, else bit=0
    isFallingEdge = debouncedChanged & ~debounced;

    //bit=1 if last debounced changed from 0 to 1, else bit=0
    isRisingEdge = debouncedChanged & debounced;

    for (readPosition=1, i=0; i < keyCount; readPosition<<=1, i++) //for each key in row
    {
        //release before press avoids impossible key sequence
        if (readPosition & isFallingEdge)       //if key was released
        {
            ptrsKeys[i]->release();
        }

        if (readPosition & isRisingEdge)        //if key was pressed
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
