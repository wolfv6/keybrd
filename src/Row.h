#ifndef ROW_H
#define ROW_H

#include <RowBase.h>
#include <Debouncer_4Samples.h>

/*
Configuration
-------------
define and initilize DELAY_MICROSECONDS in sketch.
    const unsigned int RowBase::DELAY_MICROSECONDS = 0;

Instantiation
-------------
 todo - see Row_DH
*/
class Row : public RowBase
{
    private:
        Debouncer_4Samples debouncer;
        virtual uint8_t debounce(const uint8_t rowState);
    public:
        Row( RowPort &refRowPort, const uint8_t rowPin,
            ColPort *const ptrsColPorts[], const uint8_t colPortCount, Key *const ptrsKeys[])
            : RowBase(refRowPort, rowPin, ptrsColPorts, colPortCount, ptrsKeys)
        {
            Debouncer_4Samples debouncer;
        }
};
#endif
