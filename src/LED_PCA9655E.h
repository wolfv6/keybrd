#ifndef LED_PCA9655E_H
#define LED_PCA9655E_H
#include <Arduino.h>
#include <inttypes.h>
#include <Wire.h>
#include <LED.h>
#include "IOEPort.h"

/* A LED_PCA9655E object is an PCA9655E pin that is connected to an LED indicator light.
Input/Ouput Direction configuration is set to ouput in row_Port_PCA9655E.begin() and col_Port_PCA9655E.begin().
*/
class LED_PCA9655E: public LED
{
    private:
        IOEPort& port;
        const uint8_t outputByteCommand;        //General Purpose Input/Ouput register address
        const uint8_t pin;                      //bitwise pin to LED

    public:
        LED_PCA9655E(IOEPort& port, const uint8_t pin)
            : port(port), outputByteCommand(port.num + 2), pin(pin) {}

        virtual void on();
        virtual void off();
};
#endif
