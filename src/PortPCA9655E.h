#ifndef PORTPCA9655E_H
#define PORTPCA9655E_H
#include <Arduino.h>
#include <inttypes.h>
#include <Wire.h>
#include <PortInterface.h>

/*
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
    PortPCA9655E  portB(IOE_ADDR, 1, 0);        //all pins are set to output for strobes and LEDs
    PortPCA9655E  portA(IOE_ADDR, 0, 1<<0 | 1<<1 ); //first two pins are set to input for reading,
                                                //remaining pins can be used for LEDs

Diode orientation
 ----------------
Diode orientation is explained in keybrd_library_user_guide.md > Diode orientation

PCA9655E data sheet
 ----------------
 http://www.onsemi.com/pub_link/Collateral/PCA9655E-D.PDF
*/

class PortPCA9655E : public PortInterface
{
    private:
        const uint8_t deviceAddr;
        const uint8_t portNum;                  //port identification number
        uint8_t outputVal;                      //bit pattern for strobe and LEDs
        const uint8_t readPins;                 //bit pattern, IODIR 0=output, 1=input
    public:
        PortPCA9655E(const uint8_t deviceAddr, const uint8_t portNum, const uint8_t readPins)
            : deviceAddr(deviceAddr), portNum(portNum), outputVal(0), readPins(readPins) {}
        void beginProtocol();
        void begin(const uint8_t strobeOn);
        virtual void write(const uint8_t pin, const bool logicLevel);
        virtual uint8_t read();
};
#endif
