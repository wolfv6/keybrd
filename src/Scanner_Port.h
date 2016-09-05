#ifndef SCANNER_PORT_H
#define SCANNER_PORT_H

#include <Arduino.h>
#include <inttypes.h>
#include <PortWriteInterface.h>
#include <PortReadInterface.h>

/* Scanner_Port uses bit manipulation to read all pins of one port.
The ports are normally from an I/O Expander, but could also be ports from an AVR uC.
The maximum keys per row is 8, because ports have a maximum of 8 pins each.

keybrd_library_developer_guide.md has instructions for ## Active state and diode orientation
*/
class Scanner_Port
{
    private:
        static const bool STROBE_ON;        //HIGH or LOW logic level of strobe on, active state
        static const bool STROBE_OFF;       //logic level of strobe off, complement of STROBE_ON
        PortWriteInterface& refPortWrite;            //the IC port containing the strobePin
        PortReadInterface& refPortRead;              //the IC's read port
    public:
        Scanner_Port(PortWriteInterface &refPortWrite, PortReadInterface& refPortRead)
            : refPortWrite(refPortWrite), refPortRead(refPortRead) {}
        uint8_t scan(const uint8_t strobePin);
};
#endif
