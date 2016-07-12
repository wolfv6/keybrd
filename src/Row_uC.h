#ifndef ROW_UC_H
#define ROW_UC_H

#include <Row.h>
#include <Scanner_uC.h>
#include <Debouncer_4Samples.h>

/* Row_uC is a row connected to a micro controller.

Instantiation
-------------
Definition of DELAY_MICROSECONDS is explained in Row.cpp.
Example instantiation of a row:

    const unsigned int Row::DELAY_MICROSECONDS = 1000;
    const bool Scanner_uC::STROBE_ON = LOW;   //logic level of strobe on
    const bool Scanner_uC::STROBE_OFF = HIGH; //logic level of strobe off

    const uint8_t readPins[] = {0,1,2,3,7,8};
    const uint8_t READ_PIN_COUNT = sizeof(readPins)/sizeof(*readPins);

    Key* const ptrsKeys_0[] = { &k_00, &k_01, &k_02, &k_03, &k_04, &k_05 };
    Row_uC row_0(21, readPins, READ_PIN_COUNT, ptrsKeys_0);

Number of readPins should equal number of keys in ptrsKeys_0[] array.
    if a readPins is missing, a key will be unresposive
    if a Key pointer is missing, the keyboard will fail in an unprdictable way
*/
class Row_uC : public Row
{
    private:
        Scanner_uC scanner;
        Debouncer_4Samples debouncer;
    public:
        Row_uC(const uint8_t strobePin, const uint8_t READ_PINS[], const uint8_t READ_PIN_COUNT,
                Key *const ptrsKeys[])
            : Row(ptrsKeys), scanner(strobePin, READ_PINS, READ_PIN_COUNT) { }
        void process();
};
#endif
