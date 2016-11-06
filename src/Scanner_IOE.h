#ifndef SCANNER_PORT_H
#define SCANNER_PORT_H

#include <Arduino.h>
#include <inttypes.h>
#include <ScannerInterface.h>
#include <PortInterface.h>

/* Scanner_IOE uses bit manipulation to read all pins of one port.
The maximum keys per row is 8, because ports have a maximum of 8 pins each.

begin() should be called once from sketch setup().

keybrd_library_developer_guide.md has instructions for ## Active state and diode orientation
*/
class Scanner_IOE : public ScannerInterface
{
    private:
        const bool activeState;                    //logic level of strobe on, HIGH or LOW
        PortInterface& refPortWrite;            //the IC port containing the strobePin
        PortInterface& refPortRead;             //the IC's read port
    public:
        Scanner_IOE(const bool activeState, PortInterface &refPortWrite, PortInterface& refPortRead)
            : activeState(activeState) refPortWrite(refPortWrite), refPortRead(refPortRead) {}
        void init(const uint8_t strobePin);
        void begin();
        read_pins_t scan(const uint8_t strobePin);
};
#endif
