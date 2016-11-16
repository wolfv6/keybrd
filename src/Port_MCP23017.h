#ifndef PORT_MCP23017_H
#define PORT_MCP23017_H
#include <Arduino.h>
#include <inttypes.h>
#include <Wire.h>
#include <PortInterface.h>

/*
write pins are connected to matrix Row (strobe pin) or LED.
readPins are connected to matrix column to read which keys are pressed.

Instantiation
 ------------
Example instantiation:
    const uint8_t IOE_ADDR = 0x20;              //all three MCP23017 ADDR pins pins grounded
    Port_MCP23017  portB(IOE_ADDR, 1, 0);       //all pins are set to output for strobes and LEDs
    Port_MCP23017  portA(IOE_ADDR, 0, 1<<0 | 1<<1 ); //pin 0 and pin 1 are set to input for reading,
                                                //remaining pins can be used for LEDs

Diode orientation
 ----------------
Diode orientation is explained in keybrd_library_user_guide.md > Diode orientation
*/

class Port_MCP23017 : public PortInterface
{
    private:
        const uint8_t deviceAddr;
        const uint8_t portNum;                  //port identification number, 0=A, 1=B
        uint8_t outputVal;                      //bit pattern for strobe and LEDs
        const uint8_t readPins;                 //bit pattern, IODIR 0=output, 1=input
    public:
        Port_MCP23017(const uint8_t deviceAddr, const uint8_t portNum, const uint8_t readPins)
            : deviceAddr(deviceAddr), portNum(portNum), outputVal(0), readPins(readPins) {}
        void beginProtocol();
        void begin(const uint8_t activeState);
        virtual void writeLow(const uint8_t pin);
        virtual void writeHigh(const uint8_t pin);
        virtual uint8_t read();
};
#endif
