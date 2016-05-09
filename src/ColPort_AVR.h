#ifndef COLPORT_AVR_H
#define COLPORT_AVR_H
#include <Arduino.h>
#include <inttypes.h>
#include <ColPort.h>

/* One AVR microcontroller port connected to matrix columns.

Instantiation
 ------------
The constructor configures column's DDRx and PORTx.
The 'x' in parameters DDRx, PORTx, and PINx should all be the same letter.

colPins is port's bitwise pin configuration
    1=configure as input (for pins connected to column)
    0=configure as output (for LED or not connected to a column)

Example instantiation on column port B, with pins 2 and 3 connected to columns:
    ColPort_AVR colPortB(DDRB, PORTB, PINB, 1<<2 | 1<<3 );

colPins are read from pin 0 on up.

Diode orientation
 ----------------
Rows, columns, and diode orientation are explained in Matrix.h
*/
class ColPort_AVR : public ColPort
{
    private:
        const volatile unsigned char& DDR;      //Data Direction Register, Direction: 0=Input
        const volatile unsigned char& PORT;     //PORT register
        const volatile unsigned char& PIN;      //PIN read register
    public:
        //The constructor initialization list is in .cpp
        ColPort_AVR(volatile unsigned char& DDRx, volatile unsigned char& PORTx,
                    volatile unsigned char& PINx, const uint8_t colPins);

        //read port and store result in portState
        virtual void read();
};
#endif
