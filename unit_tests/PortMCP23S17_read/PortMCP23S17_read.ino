/* unit test for PortMCP23S17
Picture of hardware is in unit_tests/PortMCP23S17_read/PortMCP23S17_bb.JPG
The setup is an MCP23S17 I/O expander on a Teensy LC controller.
MCP23S17 port-B pins are alternately grounded and energized.
portBState is a bitwise reading of port B.
output is: 10101010
*/

#include "PortIOE.h"
#include "PortMCP23S17.h"

const uint8_t PortIOE::DEVICE_ADDR = 0x20;      //MCP23S17 address, all 3 ADDR pins are grounded
PortIOE portB(1);

PortMCP23S17 portBRead(portB, ~0);

void setup()
{
    uint8_t portBState;                         //bit pattern

    delay(6000);
    portBRead.begin(HIGH);                      //HIGH or LOW, not matter

    portBState = portBRead.read();
    Keyboard.print("portBState = ");
    Keyboard.println(portBState, BIN);          //prints 10101010
}

void loop() { }
