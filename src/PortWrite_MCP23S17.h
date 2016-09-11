#ifndef PORTWRITE_MCP23S17_H
#define PORTWRITE_MCP23S17_H
#include <Arduino.h>
#include <inttypes.h>
#include <SPI.h>
#include <PortWriteInterface.h>
#include "PortIOE.h"

/* One MCP23S17 I/O expander port connected to matrix rows.
write() can output logiclevel to strobePin, one LED pin, or multiple pins.

This class has Slave Select hardcoded to Arduino Pin 10.
Arduino Pin 10 avoids the speed penalty of digitalWrite.

Instantiation
 ------------
Example instantiation:
    const uint8_t PortIOE::DEVICE_ADDR = 0x20;      //MCP23S17 address, all 3 ADDR pins are grounded
    PortIOE port_B(1);
    PortWrite_MCP23S17 portWrite_B(port_B);

Diode orientation
 ----------------
Diode orientation is explained in keybrd_library_user_guide.md > Diode orientation

MCP23S17 data sheet
 ------------------
 http://www.onsemi.com/pub_link/Collateral/MCP23S17-D.PDF
*/

class PortWrite_MCP23S17 : public PortWriteInterface
{
    private:
        PortIOE& port;
        void push(const uint8_t registerAddr, const uint8_t data);
    public:
        PortWrite_MCP23S17(PortIOE& port) : port(port) {}
        void begin();
        virtual void write(const uint8_t pin, const bool logicLevel);
};
#endif
