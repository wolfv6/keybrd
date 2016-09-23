/* unit test for PortMCP23S17
Picture of hardware is in unit_tests/PortMCP23S17_read/PortMCP23S17_bb.JPG
The setup is an MCP23S17 I/O expander on a Teensy LC controller.
MCP23S17 port-A GPIO pins are not connected to anything.
Port-A GPIO-pin ouputs alternate between 0 and 3.3 volts.

Use a volt meter to measure port-A GPIO-pin outputs.
OR low-voltage LED, with forward voltage less than 2 volts.
*/
#include "PortIOE.h"
#include "PortMCP23S17.h"

const uint8_t PortIOE::DEVICE_ADDR = 0x20;      //MCP23S17 address, all 3 ADDR pins are grounded
PortIOE portA(0);

PortMCP23S17 portAWrite(portA, 0);              //PortAWrite needed for begin()

//const uint8_t GPIOA = 0x12;                     //LEDs are on port A

void setup()
{
    delay(6000);
    portAWrite.begin(LOW);                     //HIGH or LOW, not matter if readPins=0
    Keyboard.print("start writing");
}

void loop()
{
    portAWrite.write(~0, HIGH);             //set all GPIOA pins HIGH
    delay(2000);

    portAWrite.write(~0, LOW);              //set all GPIOA pins LOW
    delay(2000);
}
