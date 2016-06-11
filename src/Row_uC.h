#ifndef ROW_H
#define ROW_H

#include <RowBase.h>
#include <RowScanner_PinsArray.h>
#include <Debouncer_4Samples.h>

/* Row_uC is a row connected to a micro controller.
Configuration
-------------
Define and initilize DELAY_MICROSECONDS in sketch.  Detailed how to is in RowBase.cpp.

Instantiation
-------------
Example instantiation of a row:

    const uint8_t colPins[] = {0,1,2,3,7,8};
    const uint8_t COL_PIN_COUNT = sizeof(colPins)/sizeof(*colPins);

    Key* const ptrsKeys_0[] = { &k_00, &k_01, &k_02, &k_03, &k_04, &k_05 };
    Row_DH_uC row_0(21, colPins, COL_PIN_COUNT, ptrsKeys_0);

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
        Row_uC(const uint8_t strobePin, const uint8_t readPins[], const uint8_t READ_PIN_COUNT,
                Key *const ptrsKeys[])
            : RowBase(ptrsKeys), scanner(strobePin, readPins, READ_PIN_COUNT) { }
        uint8_t scan(uint16_t& rowEnd);
        uint8_t debounce(const uint8_t rowState, uint8_t& debounced);
};
#endif
