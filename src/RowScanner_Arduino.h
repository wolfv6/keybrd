#ifndef ROWSCANNER_ARDUINO_H
#define ROWSCANNER_ARDUINO_H
#include <Arduino.h>
#include <inttypes.h>
#include <RowScannerInterface.h>
#include <RowPort.h>
#include <ColPort.h>
/* rowPin > strobePins[]
replace port calls with
  x pass 1: hard code pins for row0 and col6, init in setup()
  x pass 2: readPins[] array
    pass 3: move calls to IC classes - Strobe_uC, Read_uC
    pass 4: add IC classes Strobe_MCP23018, Read_MCP23018 */
class RowScanner_Arduino : public RowScannerInterface
{
    private:
        static const bool activeHigh;           //logic level of strobe pin: 0=activeLow, 1=activeHigh
        const uint8_t strobePin;                 //Arduino pin number connected to this row
        const uint8_t* readPins;                //array of read pins
        const uint8_t READ_PIN_COUNT;//todo READ_PIN_COUNT
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

