#ifndef ROWSCANNER_PINSARRAY_H
#define ROWSCANNER_PINSARRAY_H
#include <Arduino.h>
#include <inttypes.h>
#include <RowScannerInterface.h>
#include <RowPort.h>
#include <ColPort.h>

/* RowScanner_PinsArray class uses Arduino pin numbers (not port pin numbers).
*/
class RowScanner_PinsArray : public RowScannerInterface
{
    private:
        static const bool activeHigh;           //logic level of strobe pin: 0=activeLow, 1=activeHigh
        const uint8_t strobePin;                //Arduino pin number connected to this row
        const uint8_t* readPins;                //array of read pin numbers
        const uint8_t READ_PIN_COUNT;           //number of read pins
    public:
        RowScanner_PinsArray(const uint8_t strobePin,
                const uint8_t readPins[], const uint8_t READ_PIN_COUNT);
        virtual uint8_t scan(uint16_t& rowEnd);
        uint8_t getRowState(uint16_t& rowEnd);
};
#endif

