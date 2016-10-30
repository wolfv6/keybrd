/* unit test for PortMCP23S17
Picture of hardware is in unit_tests/PortMCP23S17_read/PortMCP23S17_bb.JPG
The setup is an MCP23S17 I/O expander on a Teensy LC controller.
MCP23S17 port-B pins are alternately grounded and energized.
output is: 10101010
*/

#include "Port_MCP23S17.h"

const uint8_t IOE_ADDR = 0x20;                  //MCP23S17 address, all 3 ADDR pins grounded
Port_MCP23S17 portB(IOE_ADDR, 1, ~0);           //read all pins

void setup()
{
    uint8_t BitPattern;                         //reading of port B

    delay(6000);
    portB.begin(HIGH);                          //HIGH or LOW, does not matter

    BitPattern = portB.read();
    Keyboard.print("BitPattern = ");
    Keyboard.println(BitPattern, BIN);          //prints 10101010
}

void loop() { }
