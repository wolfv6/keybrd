/* this works
The setup is an MCP23S17 I/O expander on a Teensy LC controller.
MCP23S17 port B pins are alternately grounded and energized.
portBState is a bitwise reading of port B.
output is: 10101010

posted on http://arduino.stackexchange.com/questions/tagged/spi
http://arduino.stackexchange.com/questions/28792/reading-an-mcp23s17-i-o-expander-port-with-the-arduino-spi-library
*/
#include <SPI.h>

const uint8_t ADDR = 0x20;              //MCP23S17 address, all 3 ADDR pins are grounded
const uint8_t OPCODE_READ  = (ADDR << 1 | 0x01); //MCP23S17 opcode read has LSB set

const uint8_t IODIRB = 0x01;
const uint8_t GPIOB  = 0x13;

uint8_t portBState = 0;                 //bit wise

void setup()
{
    Serial.begin(9600);
    delay(1000);

    pinMode(SS, OUTPUT);                //configure controller's Slave Select pin to output
    digitalWrite(SS, HIGH);             //disable Slave Select
    SPI.begin();

    //IODIRB register is already configured to input by default

    SPI.beginTransaction(SPISettings (SPI_CLOCK_DIV8, MSBFIRST, SPI_MODE0)); //gain control of SPI bus
    digitalWrite(SS, LOW);              //enable Slave Select
      SPI.transfer(OPCODE_READ);        //read command
      SPI.transfer(GPIOB);              //register address to read data from
      portBState = SPI.transfer(0);     //save the data (0 is dummy data to send)
    digitalWrite(SS, HIGH);             //disable Slave Select
    SPI.endTransaction();               //release the SPI bus

    Serial.println(portBState, BIN);    //should print 10101010
}

void loop() { }
