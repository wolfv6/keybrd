#ifndef SCANNER_PORT_H
#define SCANNER_PORT_H

#include <Arduino.h>
#include <inttypes.h>
#include <PortWrite.h>
#include <PortRead.h>

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
        PortWrite& refPortWrite;            //the IC port containing the strobePin
        const uint8_t strobePin;            //bitwise, 1 indicates IC pin connected to this row
        PortRead& refPortRead;              //the IC's read port
    public:
        Scanner_Port(PortWrite &refPortWrite, const uint8_t strobePin, PortRead& refPortRead)
            : refPortWrite(refPortWrite), strobePin(strobePin), refPortRead(refPortRead) {}
        uint8_t scan();
};
#endif
