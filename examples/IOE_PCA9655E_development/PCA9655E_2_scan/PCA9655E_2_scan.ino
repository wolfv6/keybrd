/* PCA9655E_2_scan.ino

power IO0_2 and read IO1_1 (similar to strobe and read on key matrix)

DESTINATION  PIN PIN_NUMBER  PIN   DESTINATION
       x     INT  1      24  VDD   Teensy LC 3.3V
      SCL    AD1  2      23  SDA   Teensy LC 18
      GND    AD2  3      22  SCL   Teensy LC 19
      GND  IO0_0  4      21  AD0   SCL
      GND  IO0_1  5      20  IO1_6  x
     IO1_1 IO0_2  6      19  IO1_5  x
      GND  IO0_3  7      18  IO1_4  x
      GND  IO0_4  8      17  IO1_4  x
      GND  IO0_5  9      16  IO1_3  x
       x   IO0_6 10      15  IO1_2  x
       x   IO0_7 11      14  IO1_1 IO0_2
      GND    VSS 12      13  IO1_0  x
*/
#include "Wire.h"

const uint8_t ADDR  = 0x18;                     //I2C address with AD2=GND AD1=SCL AD0=SCL
void setup()
{
    delay(1000);
    Serial.print("PCA9655E_read.ino");
    Wire.begin();

    //Configure port 1 to output
    Wire.beginTransmission(ADDR);
    Wire.write(7);                              //command byte 7 = Configuration dir Port 1
    Wire.write(0);                              //0=output
    Wire.endTransmission();

    Wire.beginTransmission(ADDR);
    Wire.write(3);                              //command byte 3 = Output Port 1
    Wire.write( 1<<1 );                         //1=high
    Wire.endTransmission();

    //Configure port 0 to input
    Wire.beginTransmission(ADDR);
    Wire.write(6);                              //command byte 6 = Configuration dir Port 0
    Wire.write(~0);                             //1=input
    Wire.endTransmission();
    
    Wire.beginTransmission(ADDR);
    Wire.write(0);                              //command byte 0 = Input Port 0
    Wire.endTransmission(false);                //PCA9655E needs false to send a restart

    Wire.requestFrom(ADDR, 1u);                 //request one byte from input port

    Serial.print("  port0_val= ");
    uint8_t port0_val = Wire.read();
    Serial.print(port0_val, BIN);               //expect xx000100
}

void loop() { }
