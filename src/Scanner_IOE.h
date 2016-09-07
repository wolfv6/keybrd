#ifndef SCANNER_PORT_H
#define SCANNER_PORT_H

#include <Arduino.h>
#include <inttypes.h>
#include <Wire.h>
#include <ScannerInterface.h>
#include <PortWriteInterface.h>
#include <PortReadInterface.h>

/* Scanner_IOE uses bit manipulation to read all pins of one port.
The ports are normally from an I/O Expander, but could also be ports from an AVR uC.
The maximum keys per row is 8, because ports have a maximum of 8 pins each.

keybrd_library_developer_guide.md has instructions for ## Active state and diode orientation
*/
class Scanner_IOE : public ScannerInterface
{
    private:
        const bool strobeOn;                    //logic level of strobe on, HIGH or LOW
        const bool strobeOff;                   //logic level of strobe off, complement of strobeOn
        PortWriteInterface& refPortWrite;       //the IC port containing the strobePin
        PortReadInterface& refPortRead;         //the IC's read port
    public:
        Scanner_IOE(const bool strobeOn,
                PortWriteInterface &refPortWrite, PortReadInterface& refPortRead)
            : strobeOn(strobeOn), strobeOff(!strobeOn),
            refPortWrite(refPortWrite), refPortRead(refPortRead) {}
        void init(const uint8_t strobePin);
        void begin();
        read_pins_t scan(const uint8_t strobePin);
};
#endif
