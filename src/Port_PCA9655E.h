#ifndef PORT_PCA9655E_H
#define PORT_PCA9655E_H
#include <Arduino.h>
#include <inttypes.h>
#include <Wire.h>
#include "PortInterface.h"

/* Port_PCA9655E
write pins are connected to matrix Row (strobe pin) or LED.
readPins are connected to matrix column to read which keys are pressed.

Be careful with the deviceAddr.
Table 6 in PCA9655E datasheet lists 8-bit versions of I2C addresses.
The Arduino Wire library uses 7-bit addresses throughout, so drop the low bit.
For example, I2C address with AD2=GND AD1=SCL AD0=SCL,
    Table 6 lists      8-bit DEVICE_ADDR = 0x30 (b 00110000)
    while Arduino uses 7-bit DEVICE_ADDR = 0x18 (b 00011000)
http://playground.arduino.cc/Main/WireLibraryDetailedReference

Instantiation
 ------------
Example instantiation:
    const uint8_t IOE_ADDR = 0x20;              //PCA9655E address, all 3 ADDR pins are grounded
    Port_PCA9655E  portB(IOE_ADDR, 1, 0);       //all pins are set to output for strobes and LEDs
    Port_PCA9655E  portA(IOE_ADDR, 0, 1<<0 | 1<<1 ); //pin 0 and pin 1 are set to input for reading,
                                                //remaining pins can be used for LEDs

Diode orientation
 ----------------
Diode orientation is explained in keybrd_library_user_guide.md > Diode orientation

*/

class Port_PCA9655E : public PortInterface
{
    private:
        const uint8_t deviceAddr;
        const uint8_t portNum;                  //port identification number
        uint8_t outputVal;                      //bit pattern for strobe and LEDs
        const uint8_t readPins;                 //bit pattern, IODIR 0=output, 1=input
    public:
        Port_PCA9655E(const uint8_t deviceAddr, const uint8_t portNum, const uint8_t readPins)
            : deviceAddr(deviceAddr), portNum(portNum), outputVal(0), readPins(readPins) {}
        void beginProtocol();
        void begin(const uint8_t activeState);
        virtual void writeLow(const uint8_t pin);
        virtual void writeHigh(const uint8_t pin);
        virtual uint8_t read();
};
#endif
