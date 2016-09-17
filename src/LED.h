#ifndef LED_H
#define LED_H

/* LED is an interface class
Each LED object is an IC pin that is used to power an LED on and off.
*/
class LED
{
    public:
        virtual void on()=0;
        virtual void off()=0;
};
#endif
