#ifndef ROW_H
#define ROW_H

#include <RowBase.h>
#include <RowScanner_PinsArray.h>
#include <Debouncer_4Samples.h>

/* Row_uC is a row connected to a micro controller.

Instantiation
-------------
Definition of DELAY_MICROSECONDS is explained in RowBase.cpp.
Example instantiation of a row:

    const unsigned int RowBase::DELAY_MICROSECONDS = 1000;
    const bool RowScanner_PinsArray::STROBE_ON = LOW;   //logic level of strobe on
    const bool RowScanner_PinsArray::STROBE_OFF = HIGH; //logic level of strobe off

    const uint8_t colPins[] = {0,1,2,3,7,8};
    const uint8_t COL_PIN_COUNT = sizeof(colPins)/sizeof(*colPins);

    Key* const ptrsKeys_0[] = { &k_00, &k_01, &k_02, &k_03, &k_04, &k_05 };
    Row_uC row_0(21, colPins, COL_PIN_COUNT, ptrsKeys_0);

Number of colPins should equal number of keys in ptrsKeys_0[] array.
    if a colPin is missing, a key will be unresposive
    if a Key pointer is missing, the keyboard will fail in an unprdictable way
*/
class Row_uC : public RowBase
{
    private:
        RowScanner_PinsArray scanner;
        Debouncer_4Samples debouncer;
    public:
        Row_uC(const uint8_t strobePin, const uint8_t readPins[],
                Key *const ptrsKeys[], const uint8_t KEY_COUNT)
            : RowBase(ptrsKeys), scanner(strobePin, readPins, KEY_COUNT) { }
        void process();
};
#endif
