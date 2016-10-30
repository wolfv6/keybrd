/* unit test for Port_MCP23S17
Picture of hardware is in unit_tests/PortMCP23S17_read/PortMCP23S17_bb.JPG
The setup is an MCP23S17 I/O expander on a Teensy LC controller.
MCP23S17 port-A GPIO pins are not connected to anything.
Port-A GPIO-pin ouputs alternate between 0 and 3.3 volts.

Use a volt meter to measure port-A GPIO-pin outputs or red LED.
*/
#include "Port_MCP23S17.h"

const uint8_t IOE_ADDR = 0x20;                  //MCP23S17 address, all 3 ADDR pins grounded
Port_MCP23S17 portA(IOE_ADDR , 0, 0);           //PortAWrite needed for begin()

void setup()
{
    delay(6000);
    Keyboard.println("start setup");
    portA.begin(LOW);                           //HIGH or LOW, not matter if readPins=0
    Keyboard.println("start loop");
}

void loop()
{
    portA.write(~0, HIGH);                      //set all GPIOA pins HIGH
    delay(2000);

    portA.write(~0, LOW);                       //set all GPIOA pins LOW
    delay(2000);
}
