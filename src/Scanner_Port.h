#ifndef SCANNER_PORT_H
#define SCANNER_PORT_H
#include <Arduino.h>
#include <inttypes.h>
#include <StrobePort.h>
#include <ReadPort.h>

/* Scanner_Port uses bit manipulation to read all pins of one port.
The maximum keys per row is 8, because ports have a maximum of 8 pins each.
*/
class Scanner_Port
{
    private:
        static const bool STROBE_ON;        //HIGH or LOW logic level of strobe on, active state
        StrobePort& refStrobePort;                //this row's IC port
        const uint8_t strobePin;            //bitwise, 1 indicates IC pin connected to this row
        ReadPort& refReadPort;
    public:
        Scanner_Port(StrobePort &refStrobePort, const uint8_t strobePin, ReadPort& refReadPort)
            : refStrobePort(refStrobePort), strobePin(strobePin), refReadPort(refReadPort) {}
        virtual ReadPort* const scan();
};
#endif
