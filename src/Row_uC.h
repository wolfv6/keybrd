#ifndef ROW_UC_H
#define ROW_UC_H

#include <Row.h>
#include <Scanner_uC.h>
#include <Debouncer_Samples.h>

/* Row_uC is a row connected to a micro controller.

Instantiation
-------------
keybrd_library_developer_guide.md has instructions for ## Active state and diode orientation
Example instantiation of a Row_uC:

    const bool Scanner_uC::STROBE_ON = LOW;   //logic level of strobe on, active low
    const bool Scanner_uC::STROBE_OFF = HIGH; //logic level of strobe off

    const uint8_t readPins[] = {0,1,2,3,7,8};
    const uint8_t readPinCount = sizeof(readPins)/sizeof(*readPins);

    Key* const ptrsKeys_0[] = { &k_00, &k_01, &k_02, &k_03, &k_04, &k_05 };
    Row_uC row_0(21, readPins, readPinCount, ptrsKeys_0);

Number of readPins should equal number of keys in ptrsKeys_0[] array.
    if a readPins is missing, a key will be unresposive
    if a Key pointer is missing, the keyboard will fail in an unpredictable way
*/
class Row_uC : public Row
{
    private:
        Scanner_uC scanner;
        Debouncer_Samples debouncer;
        const uint8_t readPinCount;
    public:
        Row_uC(const uint8_t strobePin, const uint8_t readPins[], const uint8_t readPinCount,
               Key* const ptrsKeys[])
            : Row(ptrsKeys), scanner(strobePin, readPins, readPinCount),
              readPinCount(readPinCount) { }
        void process();
};
#endif
