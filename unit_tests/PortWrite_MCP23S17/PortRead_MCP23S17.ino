/* unit test for PortRead_MCP23S17
The setup is an MCP23S17 I/O expander on a Teensy LC controller.
MCP23S17 port-A GPIO pins are not connected to anything.
Port-A GPIO-pin ouputs alternate between 0 and 3.3 volts.

Use a volt meter to measure port-A GPIO-pin ouputs.
MCP23S17 on 3.3v does not output enough power to reliable light LEDs
    LED lights w/o resistor
    LED not light with 56 ohm resistor
*/
#include "PortIOE.h"
#include "PortWrite_MCP23S17.h"

const uint8_t PortIOE::DEVICE_ADDR = 0x20;      //MCP23S17 address, all 3 ADDR pins are grounded
PortIOE portA(0, 0);

PortWrite_MCP23S17 portAWrite(portA);           //PortAWrite needed for begin()

const uint8_t GPIOA = 0x12;                     //LEDs are on port A

void setup()
{
    delay(6000);
    portAWrite.begin();
    //Keyboard.print("start blinking");
}

void loop()
{
    portAWrite.write(~0, HIGH);             //set all GPIOA pins HIGH
    delay(2000);

    portAWrite.write(~0, LOW);              //set all GPIOA pins LOW
    delay(2000);
}
