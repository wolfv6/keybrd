#ifndef ROWSCANNER_PINSBITWISE_H
#define ROWSCANNER_PINSBITWISE_H
#include <Arduino.h>
#include <inttypes.h>
#include <RowPort.h>
#include <ColPort.h>

/* RowScanner_PinsBitwise uses bit manipulation to read all pins of one port.
The maximum keys per row is 8, because ports have a maximum of 8 pins each.
*/
class RowScanner_PinsBitwise
{
    private:
        RowPort& refRowPort;                //this row's IC port
        const uint8_t strobePin;            //bitwise, 1 indicates IC pin connected to this row
        ColPort& refColPort;
    public:
        RowScanner_PinsBitwise(RowPort &refRowPort, const uint8_t strobePin,
            ColPort& refColPort)
            : refRowPort(refRowPort), strobePin(strobePin),
              refColPort(refColPort) {}
        static const bool STROBE_ON;        //logic level of strobe on, active state, HIGH or LOW
        virtual ColPort* const scan();
};
#endif
