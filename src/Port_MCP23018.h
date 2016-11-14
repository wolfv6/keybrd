#ifndef PORT_MCP23018_H
#define PORT_MCP23018_H
#include <Arduino.h>
#include <inttypes.h>
#include <Wire.h>
#include <PortInterface.h>

/*
write pins are connected to matrix Row (strobe pin) or LED.
readPins are connected to matrix column to read which keys are pressed.

MCP23018 has open-drain outputs (open-drain can only sink current).  If LEDs are used, connect:
    LED anodes (the longer lead) to power
    LED cathodes (the shorter lead) to GPIO pin

Instantiation
 ------------
Example instantiation:
    const uint8_t IOE_ADDR = 0x20;              //MCP23018 address pin grounded
    Port_MCP23018  portB(IOE_ADDR, 1, 0);       //all pins are set to output for strobes and LEDs
    Port_MCP23018  portA(IOE_ADDR, 0, 1<<0 | 1<<1 ); //pin 0 and pin 1 are set to input for reading,
                                                //remaining pins can be used for LEDs

Diode orientation
 ----------------
Diode orientation is explained in keybrd_library_user_guide.md > Diode orientation

MCP23018 data sheet
 ----------------
 http://ww1.microchip.com/downloads/en/DeviceDoc/22103a.pdf
*/

class Port_MCP23018 : public PortInterface
{
    private:
        const uint8_t deviceAddr;
        const uint8_t portNum;                  //port identification number, 0=A, 1=B
        uint8_t outputVal;                      //bit pattern for strobe and LEDs
        const uint8_t readPins;                 //bit pattern, IODIR 0=output, 1=input
    public:
        Port_MCP23018(const uint8_t deviceAddr, const uint8_t portNum, const uint8_t readPins)
            : deviceAddr(deviceAddr), portNum(portNum), outputVal(0), readPins(readPins) {}
        void beginProtocol();
        void begin(const uint8_t strobeOn);
        virtual void setLow(const uint8_t pin);
        virtual void setHigh(const uint8_t pin);
        virtual uint8_t read();
};
#endif
