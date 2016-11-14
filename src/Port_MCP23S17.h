#ifndef PORT_MCP23S17_H
#define PORT_MCP23S17_H
#include <Arduino.h>
#include <inttypes.h>
#include <SPI.h>
#include <PortInterface.h>

/*
write pins are connected to matrix Row (strobe pin) or LED.
readPins are connected to matrix column to read which keys are pressed.

Slave Select is hardcoded to Arduino Pin 10.
Arduino Pin 10 avoids the speed penalty of digitalWrite.

Instantiation
 ------------
MCP23S17 datasheet identifies ports by letters, while class Port_MCP23S17 uses portNum
    for port A, use portNum=0
    for port B, use portNum=1
readPins parameter configures port's pins.

Example instantiation:
    const uint8_t IOE_ADDR = 0x20;              //MCP23S17 address, all 3 ADDR pins are grounded
    Port_MCP23S17 portB(IOE_ADDR, 1, 0);        //all pins are set to output for strobes and LEDs
    Port_MCP23S17 portA(IOE_ADDR, 0, 1<<0 | 1<<1 ); //pin 0 and pin 1 are set to input for reading,
                                                //remaining pins can be used for LEDs

Diode orientation
 ----------------
Diode orientation is explained in keybrd_library_user_guide.md > Diode orientation

MCP23S17 data sheet
 ------------------
 http://www.onsemi.com/pub_link/Collateral/MCP23S17-D.PDF
*/
class Port_MCP23S17 : public PortInterface
{
    private:
        const uint8_t deviceAddr;
        const uint8_t portNum;                  //port identification number
        uint8_t outputVal;                      //bit pattern for strobe and LEDs
        const uint8_t readPins;                 //bit pattern, IODIR 0=output, 1=input
        uint8_t transfer(const uint8_t command, const uint8_t registerAddr, const uint8_t data);
    public:
        Port_MCP23S17(const uint8_t deviceAddr, const uint8_t portNum, const uint8_t readPins)
            : deviceAddr(deviceAddr), portNum(portNum), outputVal(0), readPins(readPins) {}
        void beginProtocol();
        void begin(const uint8_t strobeOn);
        virtual void setLow(const uint8_t pin);
        virtual void setHigh(const uint8_t pin);
        virtual uint8_t read();
};
#endif
