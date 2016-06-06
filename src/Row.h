#ifndef ROW_H
#define ROW_H

#include <RowBase.h>
//#include <RowScanner_BitManipulation.h>
#include <RowScanner_Arduino.h>
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
        //RowScanner_BitManipulation scanner;
        RowScanner_Arduino scanner;
        Debouncer_4Samples debouncer;
    public:
        //Row constructor was like Row_DH constructor
        Row(const uint8_t rowPin, Key *const ptrsKeys[]) : RowBase(ptrsKeys), scanner(rowPin) { }
        virtual void process();
};
#endif
