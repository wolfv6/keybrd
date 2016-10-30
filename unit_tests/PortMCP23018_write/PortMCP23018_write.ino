/* unit test for Port_MCP23018
Picture of hardware is in unit_tests/PortMCP23018_read/PortMCP23018_bb.JPG todo
The setup is an MCP23018 I/O expander on a Teensy LC controller.
MCP23018 port-A GPIO pins are not connected to anything.
Port-A GPIO-pin ouputs alternate between 0 and 3.3 volts.
volt meter between pin A1 and power because
 MCP23018 has open-drain outputs (open-drain can only sink current)

Use a volt meter to measure port-A GPIO-pin outputs or red LED.
*/
#include "Port_MCP23018.h"

const uint8_t IOE_ADDR = 0x20;                  //MCP23018 address ADDR pin grounded
Port_MCP23018 portA(IOE_ADDR, 0, 0);

void setup()
{
    delay(6000);
    Keyboard.println("PortMCP23018_write.ino");
    portA.beginProtocol();
    portA.begin(LOW);                           //HIGH or LOW, not matter if readPins=0
}

void loop()
{
    portA.write(~0, HIGH);                      //set all GPIOA pins HIGH
    Keyboard.print("+");
    delay(2000);

    portA.write(~0, LOW);                       //set all GPIOA pins LOW
    Keyboard.print("0");
    delay(2000);
}
