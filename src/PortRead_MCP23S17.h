#ifndef PORTREAD_MCP23S17_H
#define PORTREAD_MCP23S17_H
#include <Arduino.h>
#include <inttypes.h>
#include <SPI.h>
#include <PortReadInterface.h>
#include "PortMCP23S17.h"
#include "PortIOE.h"
#include "Scanner_IOE.h"

/* One MCP23S17 I/O expander port connected to matrix columns.

This class has Slave Select hardcoded to Arduino Pin 10.
Arduino Pin 10 avoids the speed penalty of digitalWrite.

Instantiation
 ------------
readPins parameter is port's bit pattern pin configuration
    1=configure as input (for read pins connected to column)
    0=configure as output (for LED or not connected to a column)
readPins are read from pin 0 on up.

Example instantiation with port-A pins 0 and 1 connected to Scanner_IOE columns:
    const uint8_t PortIOE::DEVICE_ADDR = 0x20;      //MCP23S17 address, all 3 ADDR pins are grounded
    PortIOE port_A(0);
    PortRead_MCP23S17 portRead_A(port_A, 1<<0 | 1<<1 );

Diode orientation
 ----------------
Diode orientation is explained in keybrd_library_user_guide.md > Diode orientation

MCP23S17 data sheet
 ------------------
 http://www.onsemi.com/pub_link/Collateral/MCP23S17-D.PDF
*/
class PortRead_MCP23S17 : public PortReadInterface, public PortMCP23S17
{
    private:
        PortIOE& port;
        uint8_t pullUp;                         //bits, 1 means internal pull-up resistor enabled
        const uint8_t readPins;                 //bits, 1 means internal pull-up resistor enabled
    public:
        PortRead_MCP23S17(PortIOE& port, const uint8_t readPins)
            : port(port), readPins(readPins) {}
        void begin(const uint8_t strobeOn);
        virtual uint8_t read();
};
#endif
