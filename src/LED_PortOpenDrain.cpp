#include "LED_PortOpenDrain.h"
/* functions are like LED_Port, but writeLow() writeHigh() are swapped.
*/
void LED_PortOpenDrain::on()
{
    refPort.writeLow(pin);
}

void LED_PortOpenDrain::off()
{
    refPort.writeHigh(pin);
}
