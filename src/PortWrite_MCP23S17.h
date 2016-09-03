#ifndef PORTWRITE_MCP23S17_H
#define PORTWRITE_MCP23S17_H
#include <Arduino.h>
#include <inttypes.h>
#include <SPI.h>
#include <PortWrite.h>
#include "PortIOE.h"

/* One MCP23S17 I/O expander port connected to matrix rows.
MCP23S17 does not have internal pull-up resistors (PCA9535E does).

begin() configures column port's configuration and output.
This should normally be called once in sketch's setup().
If PortRead_MCP23S17 is instantiated on the same port, do NOT use PortWrite_MCP23S17::begin().
Otherwise readPins could be overwritten.

Instantiation
 ------------
Example instantiation for row port 0:
    PortIOE port0(0, 0);
    PortWrite_MCP23S17 rowPort0(port0);

Example instantiation for row port 1:
    PortIOE port1(1, 0);
    PortWrite_MCP23S17 rowPort1(port1);

Diode orientation
 ----------------
Diode orientation is explained in keybrd_library_user_guide.md > Diode orientation

MCP23S17 data sheet
 ----------------
 http://www.onsemi.com/pub_link/Collateral/MCP23S17-D.PDF
*/

class PortWrite_MCP23S17 : public PortWrite
{
    private:
        PortIOE& port;
        void writePort(const uint8_t registerAddr, const uint8_t data);
    public:
        PortWrite_MCP23S17(PortIOE& port) : port(port) {}
        void begin();
        virtual void write(const uint8_t pin, const uint8_t level);
};
#endif
