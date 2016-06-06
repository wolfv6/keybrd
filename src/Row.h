#ifndef ROW_H
#define ROW_H

#include <RowBase.h>
#include <RowScanner_BitManipulation.h>
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
        RowScanner_BitManipulation scanner;
        Debouncer_4Samples debouncer;
    public:
        Row( RowPort &refRowPort, const uint8_t rowPin,
            ColPort *const ptrsColPorts[], const uint8_t colPortCount, Key *const ptrsKeys[])
            : RowBase(ptrsKeys), scanner(refRowPort, rowPin, ptrsColPorts, colPortCount) { }
        virtual void process(const bool activeHigh);
};
#endif
