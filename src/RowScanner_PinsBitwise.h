#ifndef ROWSCANNER_PINSBITWISE_H
#define ROWSCANNER_PINSBITWISE_H
#include <Arduino.h>
#include <inttypes.h>
#include <RowScannerInterface.h>
#include <RowPort.h>
#include <ColPort.h>

/* RowScanner_PinsBitwise uses bit manipulation to read all pins of one port.
*/
class RowScanner_PinsBitwise : public RowScannerInterface
{
    private:
        static const bool activeHigh;       //logic level of strobe pin: 0=activeLow, 1=activeHigh
        RowPort& refRowPort;                //this row's IC port
        const uint8_t strobePin;            //bitwise, 1 indicates IC pin connected to this row
        ColPort& refColPort;
    public:
        RowScanner_PinsBitwise(RowPort &refRowPort, const uint8_t strobePin,
            ColPort& refColPort)
            : refRowPort(refRowPort), strobePin(strobePin),
              refColPort(refColPort) {}
        virtual uint8_t scan(uint16_t& rowEnd);
        uint8_t getRowState(uint16_t& rowEnd);
};
#endif
