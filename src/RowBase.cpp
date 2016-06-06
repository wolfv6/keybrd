#include "RowBase.h"
/* wait() delay's scan to give switches time to debounce.
This version of wait() is very simple.  More sophisticated versions can override this one.

For fastest response time, wait() should be placed before scan() or after pressRelease()
 (waiting between strobe and send would unnecessarily delay send).

A keyboard with a faster scan rate responds faster.
Follow these step to tune DELAY_MICROSECONDS for maximum scan rate for a given SAMPLE_COUNT:
Initialize DELAY_MICROSECONDS in your sketch:
    const unsigned int Row::DELAY_MICROSECONDS = 1000;
Add this to the sketch's loop() function:
    debug.print_microseconds_per_scan();
Compile and load the sketch into the microcontroller; microseconds_per_scan is printed every second.
Adjust the value of DELAY_MICROSECONDS and repeat until:
    debug.print_microseconds_per_scan() <= DEBOUNCE_TIME / SAMPLE_COUNT

DEBOUNCE_TIME can be obtained from the switch's datasheet.  Some switch bounce times are:
Cherry MX specifies 5msec bounce time http://www.cherrycorp.com/english/switches/key/mx.htm
hasu measured Cherry MX bounce times .3ms to 1.4ms http://geekhack.org/index.php?topic=42385.0
Tactile switch MJTP series bounce 10 ms http://www.apem.com/files/apem/brochures/MJTP_6MM.pdf 

Avoid sampling the switch input at a rate synchronous to events in the environment
 that might create periodic EMI. For instance, 50 and 60 Hz.

Polling I2C may slow the scan rate enough so that no additional delay is needed:
    const unsigned int Row::DELAY_MICROSECONDS = 0;

Slow-scan trick for debug messages that print too fast:
    change DELAY_MICROSECONDS to a large number like 10000
That way debug messages are printed at a managable rate.
*/
void RowBase::wait()
{
    delayMicroseconds(DELAY_MICROSECONDS);      //delay between Row scans to debounce switches
}

/*
pressRelease() calls key's press() or release() function if it was pressed or released.
Both parameters are bitwise.
*/
void RowBase::pressRelease(const uint16_t rowEnd, const uint8_t debouncedChanged)
{
    uint8_t isFallingEdge;                      //1 means falling edge
    uint8_t isRisingEdge;                       //1 means rising edge
    uint8_t rowMask;                            //bitwise, active col bit is 1
    uint8_t col;                                //index for ptrsKeys[col] array

    //bit=1 if last debounced changed from 1 to 0, else bit=0
    isFallingEdge = debouncedChanged & ~debounced;

    //bit=1 if last debounced changed from 0 to 1, else bit=0
    isRisingEdge = debouncedChanged & debounced;

    for (rowMask=1, col=0; rowMask<rowEnd; rowMask<<=1, col++) //for each key in row
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
