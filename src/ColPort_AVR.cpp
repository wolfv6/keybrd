#include "ColPort_AVR.h"

/*
configures column port's DDRx and PORTx.
*/
ColPort_AVR::ColPort_AVR(volatile unsigned char& DDRx, volatile unsigned char& PORTx,
                         volatile unsigned char& PINx, const uint8_t colPins)
    : ColPort(colPins), DDR(DDRx = ~colPins), PORT(PORTx = colPins), PIN(PINx)
{}

/*
Saves all port-pin values to portState.
*/
void ColPort_AVR::read()
{
    portState = PIN;
}
