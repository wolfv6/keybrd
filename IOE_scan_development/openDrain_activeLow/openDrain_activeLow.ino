/* simulate one scan of a key martix, on open-drain active-low I/O expander

BREADBOARD SETUP *******************************
    Teensy LC connected to MCP23018 I/O expander via I2C
    4.7k Ohm pullup resistors on SDA and SCL
    use volt meter to measure pin voltages
    MCP23018 has open-drain outputs (open-drain can only sink current)

MCP23018 PIN DIAGRAM ***************************
      write port B          read port A
    GND      VSS 1          28 NC
              NC 2          27 GPA7
    jumper0 GPB0 3          26 GPA6
            GPB1 4          25 GPA5
            GPB2 5          24 GPA4  jumper4
            GPB3 6          23 GPA3
    jumper4 GPB4 7          22 GPA2
            GPB5 8          21 GPA1
            GPB6 9          20 GPA0  jumper0
            GPB7 10         19 INTA
    power    VDD 11         18 INTB
    SCL      SCL 12         17 NC
    SDA      SDA 13         16 RESET power
              NC 14         15 ADDR  GND
*/
#include "Wire.h"

const uint8_t ADDR  = 0x20;                     //MCP23018 I2C address with ADDR pin grounded

void setup()
{
    delay(1000);                                //time for Serial print to work

// ================= configure ================
    Serial.print("config ");
    Wire.begin();

    Wire.beginTransmission(ADDR);
    Wire.write(0x01);                           //IODIRB Configure
    Wire.write(0);                              //as output
    Wire.endTransmission();

    Wire.beginTransmission(ADDR);
    Wire.write(0x00);                           //IODIRA Configuration
    Wire.write(~0);                             //as input
    Wire.endTransmission();

    Wire.beginTransmission(ADDR);
    Wire.write(0x0C);                           //GPPUA pull-up
    Wire.write(~0);                             //pull-up enabled
    Wire.endTransmission();

// =================== scan ===================
    Serial.println("scan");

    Wire.beginTransmission(ADDR);
    Wire.write(0x13);                           //GPIOB output
    Wire.write(B00001111);                      //pins 0-3 off, pins 4-7 sink on (strobe, LED on)
    Wire.endTransmission();

    Wire.beginTransmission(ADDR);
    Wire.write(0x12);                           //GPIOA (immediately before requestFrom)
    Wire.endTransmission();

    Wire.requestFrom(ADDR, static_cast<uint8_t>(1)); //request one byte from GPIOA read
    Serial.print("portA=");
    Serial.println(Wire.read(), BIN);           //prints portA=11101111
}
void loop() { }
