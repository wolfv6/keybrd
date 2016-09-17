/* unit test for PortRead_MCP23S17
Picture of hardware is in unit_tests/PortRead_MCP23S17/PortRead_MCP23S17_bb.JPG
The setup is an MCP23S17 I/O expander on a Teensy LC controller.
MCP23S17 port-B pins are alternately grounded and energized.
portBState is a bitwise reading of port B.
output is: 10101010
*/

#include "PortIOE.h"
#include "PortRead_MCP23S17.h"
#include "Scanner_IOE.h"

const uint8_t PortIOE::DEVICE_ADDR = 0x20;      //MCP23S17 address, all 3 ADDR pins are grounded
PortIOE portB(1, 0);

PortRead_MCP23S17 portBRead(portB, ~0);

void setup()
{
    uint8_t portBState;                         //bit pattern

    delay(6000);
    portBRead.begin(LOW);

    portBState = portBRead.read();
    Keyboard.print("portBState = ");
    Keyboard.println(portBState, BIN);          //prints 10101010
}

void loop() { }
