#ifndef LED_H
#define LED_H

/* LED is an abstract base class
Each LED object is an IC pin that is used to power an LED on and off.

Connect the LED in series with the resistor:
    Calculate current-limiting-resistor value (100 Ohms to 10k Ohms will work with 5 volts)
        R = (Vs - Vf) / If
        http://www.digikey.com/en/resources/conversion-calculators/conversion-calculator-led-series-resistor
    Connect the LED's anode (the longer lead) to the AVR output pin (+)
    Connect the LED's cathode to ground (-)
Never connect a LED directly from ground to power.  Doing so would destroy the LED.
*/
class LED
{
    public:
        virtual void on()=0;
        virtual void off()=0;
};
#endif
