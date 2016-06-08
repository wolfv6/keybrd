#ifndef ROWSCANNER_ARDUINO_H
#define ROWSCANNER_ARDUINO_H
#include <Arduino.h>
#include <inttypes.h>
#include <RowScannerInterface.h>
#include <RowPort.h>
#include <ColPort.h>

/* RowScanner_Arduino class uses Arduino pin numbers (no port name).
*/
class RowScanner_Arduino : public RowScannerInterface
{
    private:
        static const bool activeHigh;           //logic level of strobe pin: 0=activeLow, 1=activeHigh
        const uint8_t strobePin;                //Arduino pin number connected to this row
        const uint8_t* readPins;                //array of read pin numbers
        const uint8_t READ_PIN_COUNT;           //number of read pins
    public:
        RowScanner_Arduino(const uint8_t strobePin,
                const uint8_t readPins[], const uint8_t READ_PIN_COUNT)
            : strobePin(strobePin), readPins(readPins), READ_PIN_COUNT(READ_PIN_COUNT)
        {
            //row
            pinMode(strobePin, OUTPUT);

            //cols
            for (uint8_t i=0; i < READ_PIN_COUNT; i++)
            {
                pinMode(readPins[i], INPUT_PULLUP);
            }
        }
        virtual uint8_t scan(uint16_t& rowEnd);
        uint8_t getRowState(uint16_t& rowEnd);
};
#endif

