#ifndef ROW_IOE_H
#define ROW_IOE_H

#include <Row.h>
#include <Scanner_Port.h>
#include <Debouncer_Samples.h>
class PortWriteInterface;
class PortReadInterface;

/* Row_IOE is a row connected to an Input/Output Expander.
Configuration and Instantiation instructions are in keybrd/src/Row_IOE.h
*/
class Row_IOE : public Row
{
    private:
        Scanner_Port scanner;
        Debouncer_Samples debouncer;
        const uint8_t readPinCount;             //number of read pins
    public:
        Row_IOE(PortWriteInterface& refPortWrite, const uint8_t strobePin,
                  PortReadInterface& refPortRead, const uint8_t readPinCount, Key *const ptrsKeys[])
            : Row(ptrsKeys), scanner(refPortWrite, strobePin, refPortRead),
              readPinCount(readPinCount) { }
        void process();
};
#endif
