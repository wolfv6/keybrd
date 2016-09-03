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
#include "Scanner_Port.h"

const bool Scanner_Port::STROBE_ON = LOW;
const bool Scanner_Port::STROBE_OFF = HIGH;

const uint8_t PortIOE::DEVICE_ADDR = 0x20;      //MCP23S17 address, all 3 ADDR pins are grounded
PortIOE portB(1, 0);

PortRead_MCP23S17 portBRead(portB, ~0);

void setup()
{
    uint8_t portBState;                         //bit wise

    delay(6000);
    portBRead.begin();

    portBState = portBRead.read();
    Keyboard.print("portBState = ");
    Keyboard.println(portBState, BIN);          //prints 10101010
}

void loop() { }
