/* this works with volt meter (MCP23S17 on 3.3v does not output enough power for LEDs)
LED lights w/o resistor, not light with 56 ohm resistor
blink LED on MCP23S17 port A pin
from Example 41.1 - Microchip MCP23017 with Arduino
 http://tronixstuff.com/tutorials > chapter 41
 http://tronixstuff.com/2011/08/26/tutorial-maximising-your-arduinos-io-ports/
 John Boxall | CC by-sa-nc
from http://69.5.26.215/forum/?id=10945&page=3 #35
modified to test MCP23S17 (SPI) using syntax from
 http://arduino.stackexchange.com/questions/16348/how-do-you-use-spi-on-an-arduino
 > 

SPISettings from http://arduino.stackexchange.com/questions/14191/mcp23s17-programming-iodirx-register-works-in-loop-but-not-in-setup
*/
#include <SPI.h>

const uint8_t ADDR = 0x20;              //MCP23S17 address, all ADDR pins are grounded
const uint8_t OPCODE_WRITE = (ADDR << 1);  //MCP23S17 opcode write has LSB clear

const uint8_t IODIRA = 0x00;            //LEDs are on port A
const uint8_t GPIOA  = 0x12;

uint8_t LED_state = 0;                  //bit wise

void IOEWrite(const uint8_t registerAddr, const uint8_t data)
{
    SPI.beginTransaction(SPISettings (SPI_CLOCK_DIV8, MSBFIRST, SPI_MODE0)); //slower clock
    digitalWrite(SS, LOW);              //enable Slave Select
      SPI.transfer(OPCODE_WRITE);       //write command
      SPI.transfer(registerAddr);       //register address to write data to
      SPI.transfer(data);               //data
    digitalWrite(SS, HIGH);             //disable Slave Select
    SPI.endTransaction();               //release the SPI bus
}

void setup()
{
    Serial.begin(9600);

    pinMode(SS, OUTPUT);                //configure controller's Slave Select pin to output
    digitalWrite(SS, HIGH);             //disable Slave Select
    SPI.begin();

    IOEWrite(IODIRA, 0x00);             //configure IODIRA register to output
}

void loop()
{
    IOEWrite(GPIOA, LED_state);         //set all GPIOA pins

    delay(2000);
    //Serial.println(LED_state, BIN);     //prints alternating 0 and 11111111
    LED_state = ~LED_state;             //toggle LED on/off
}
