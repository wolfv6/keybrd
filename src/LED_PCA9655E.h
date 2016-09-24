#ifndef LED_PCA9655E_H
#define LED_PCA9655E_H
#include <Arduino.h>
#include <inttypes.h>
#include <Wire.h>
#include <LED.h>
#include <PortPCA9655E.h>

/* A LED_PCA9655E object is an PCA9655E pin that is connected to an LED indicator light.
Input/Ouput Direction configuration are set to ouput in PortPCA9655E.begin() and PortRead_PCA9655E.begin().
*/
class LED_PCA9655E: public LED
{
    private:
        PortPCA9655E& refPort;
        const uint8_t pin;                      //bit pattern, IOE pin to LED

    public:
        LED_PCA9655E(PortPCA9655E& refPort, const uint8_t pin) : refPort(refPort), pin(pin) {}
        virtual void on();
        virtual void off();
};
#endif
