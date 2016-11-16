#ifndef PORT_MCP23S18_H
#define PORT_MCP23S18_H
#include "Port_MCP23S17.h"

/* Port_MCP23S18 has not been tested.
write pins are connected to matrix Row (strobe pin) or LED.
readPins are connected to matrix column to read which keys are pressed.

Port_MCP23S18 can only be active low (Scanner_IOE::activeState = LOW).
Open-drain active high would not work because pull down resistors have no effect on sink.
 https://en.wikipedia.org/wiki/Open_collector

Use LED_PortOpenDrain class for indicator LEDs.

Example instantiation:
    const uint8_t IOE_ADDR = 0x20;              //MCP23S18 address pin grounded
    Port_MCP23S18  portB(IOE_ADDR, 1, 0);       //all pins are set to output for strobes and LEDs
    Port_MCP23S18  portA(IOE_ADDR, 0, 1<<0 | 1<<1 ); //pin 0 and pin 1 are set to input for reading,
                                                //remaining pins can be used for LEDs
Diode orientation
 ----------------
Diode orientation is explained in keybrd_library_user_guide.md > Diode orientation
*/

class Port_MCP23S18 : public Port_MCP23S17
{
    public:
        Port_MCP23S18(const uint8_t deviceAddr, const uint8_t portNum, const uint8_t readPins)
            : Port_MCP23S17(deviceAddr, portNum, readPins) {}
};
#endif
