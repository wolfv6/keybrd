#include "RowPort_AVR_Optic.h"

/*
configures row port's DDRx and PORTx pins as output.
*/
RowPort_AVR_Optic::RowPort_AVR_Optic
(volatile unsigned char& DDRx, volatile unsigned char& PORTx)
    : DDR(DDRx = ~0), PORT(PORTx)
{}

/*
activePin is a port mask, where active pin is 1.
*/
void RowPort_AVR_Optic::setActivePinLow(const uint8_t activePin)
{
    PORT &= ~activePin;
}

/*
activePin is port mask, where active pin is 1.

The delayMicroseconds() is for DodoHand keyboard's optic switches.
Strobe needs to be turned on for >= 300µs before the columns are read.
During this time the state of the columns are settling into their actual values.
Seems to be necessary in order to allow the phototransistors to turn completely off.
(delay is not need for I/O expander because time between I2C Transmissions)
(Teensy2 ATMEGA32U4 16 MHz is a 0.0625 µs period)
*/
void RowPort_AVR_Optic::setActivePinHigh(const uint8_t activePin)
{
    //strobe row on
    PORT |= activePin;
    delayMicroseconds(300);                 //wait for the column value to stabilize after strobe
}
