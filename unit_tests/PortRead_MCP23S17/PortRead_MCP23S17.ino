/* unit test for PortRead_MCP23S17
The setup is an MCP23S17 I/O expander on a Teensy LC controller.
MCP23S17 port-B pins are alternately grounded and energized.
portBState is a bitwise reading of port B.
output is: 10101010

posted on http://arduino.stackexchange.com/questions/tagged/spi
http://arduino.stackexchange.com/questions/28792/reading-an-mcp23s17-i-o-expander-port-with-the-arduino-spi-library
*/
#include "PortIOE.h"
#include "PortRead_MCP23S17.h"
#include "PortWrite_MCP23S17.h"

const uint8_t PortIOE::ADDR = 0x20;             //MCP23S17 address, all 3 ADDR pins are grounded
PortIOE portB(1, 0);

PortRead_MCP23S17 portBRead(portB);
PortWrite_MCP23S17 portBWrite(portB);           //PortBWrite needed for begin()

void setup()
{
    uint8_t portBState;                         //bit wise

    delay(6000);
    portBWrite.begin();

    portBState = portBRead.read();
    Keyboard.print("portBState = ");
    Keyboard.println(portBState, BIN);          //should print 10101010
}

void loop() { }
