#ifndef PORTMCP23S17_H
#define PORTMCP23S17_H
#include <Arduino.h>
#include <inttypes.h>
#include <SPI.h>
#include <PortInterface.h>

/*
readPins are connected to matrix col
write pin is connected to matrix Row (strobe pin) or LED.

Slave Select is hardcoded to Arduino Pin 10.
Arduino Pin 10 avoids the speed penalty of digitalWrite.

Instantiation
 ------------
MCP23S17 datasheet identifies ports by letters, while class PortMCP23S17 uses portNum
    for port A, use portNum=0
    for port B, use portNum=1
readPins parameter configures port's pins.

Example instantiation:
    const uint8_t Port_MCP23S17::DEVICE_ADDR = 0x20; //MCP23S17 address, all 3 ADDR pins grounded
    Port_MCP23S17 portB(1, 0);                  //all pins are set to output for strobes and LEDs
    Port_MCP23S17 portA(0, 1<<0 | 1<<1 );       //1 pins are set to input for reading,
                                                //remaining pins can be used for LEDs

Diode orientation
 ----------------
Diode orientation is explained in keybrd_library_user_guide.md > Diode orientation

MCP23S17 data sheet
 ------------------
 http://www.onsemi.com/pub_link/Collateral/MCP23S17-D.PDF
*/
class PortMCP23S17 : public PortInterface
{
    private:
        static const uint8_t DEVICE_ADDR;
        const uint8_t portNum;                  //port identification number
        uint8_t outputVal;                      //bit pattern for strobe and LEDs
        const uint8_t readPins;                 //bits, IODIR 0=output, 1=input
        uint8_t transfer(const uint8_t command, const uint8_t registerAddr, const uint8_t data);
    public:
        PortMCP23S17(const uint8_t portNum, const uint8_t readPins)
            : portNum(portNum), outputVal(0), readPins(readPins) {}
        void beginProtocol();
        void begin(const uint8_t strobeOn);
        virtual void write(const uint8_t pin, const bool logicLevel);
        virtual uint8_t read();
};
#endif
