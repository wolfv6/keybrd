#ifndef LEDINTERFACE_H
#define LEDINTERFACE_H

/* Each LED object is an IC pin that is used to power an LED on and off.
*/
class LEDInterface
{
    public:
        virtual void on()=0;
        virtual void off()=0;
};
#endif
