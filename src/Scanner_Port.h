#ifndef SCANNER_PORT_H
#define SCANNER_PORT_H
#include <Arduino.h>
#include <inttypes.h>
#include <PortWrite.h>
#include <PortRead.h>

/* Scanner_Port uses bit manipulation to read all pins of one port.
The maximum keys per row is 8, because ports have a maximum of 8 pins each.
*/
class Scanner_Port
{
    private:
        static const bool STROBE_ON;        //HIGH or LOW logic level of strobe on, active state
        static const bool STROBE_OFF;           //logic level of strobe off, complement of STROBE_ON
        PortWrite& refPortWrite;                //this row's IC port
        const uint8_t STROBE_PIN;            //bitwise, 1 indicates IC pin connected to this row
        PortRead& refPortRead;
    public:
        Scanner_Port(PortWrite &refPortWrite, const uint8_t STROBE_PIN, PortRead& refPortRead)
            : refPortWrite(refPortWrite), STROBE_PIN(STROBE_PIN), refPortRead(refPortRead) {}
        uint8_t scan();
};
#endif
