#ifndef ROWSCANNER_PINSARRAY_H
#define ROWSCANNER_PINSARRAY_H
#include <Arduino.h>
#include <inttypes.h>
#include <config_keybrd.h>
#include <RowScannerInterface.h>
#include <RowPort.h>
#include <ColPort.h>

/* RowScanner_PinsArray class uses Arduino pin numbers (not port pin numbers).
The maximum keys per row is 31, because Arduino's largest type is 32 bits and rowEnd consumes the last bit.
Constructor is in RowScanner_PinsArray.cpp
*/
class RowScanner_PinsArray : public RowScannerInterface
{
    private:
        static const bool ACTIVE_HIGH;          //logic level of strobe pin: 0=activeLow, 1=activeHigh
        const uint8_t STROBE_PIN;               //Arduino pin number connected to this row
        const uint8_t* const READ_PINS;               //array of read pin numbers
        const uint8_t READ_PIN_COUNT;           //number of read pins
    public:
        RowScanner_PinsArray(const uint8_t STROBE_PIN,
                const uint8_t READ_PINS[], const uint8_t READ_PIN_COUNT);
        virtual read_pins_t scan(read_pins_mask_t& rowEnd);
        //read_pins_t getRowState(read_pins_mask_t& rowEnd);
};
#endif

