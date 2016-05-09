#ifndef ROWPORT_AVR_OPTIC_H
#define ROWPORT_AVR_OPTIC_H
#include <Arduino.h>
#include <inttypes.h>
#include <RowPort.h>

/* One AVR microcontroller port connected to matrix rows.

setActivePinHigh() has a delay to allow phototransistors time to sense strobe
(DodoHand has optic switches with phototransistors).

Instantiation
 ------------
The constructor configures all pins of port as output (for strobe pins and LED).
The 'x' in parameters DDRx, PORTx, and PINx should all be the same letter.

Example instantiation for row port F:
    RowPort_AVR_Optic rowPortF(DDRF, PORTF);

Diode orientation
 ----------------
Rows, columns, and diode orientation are explained in Matrix.h

*/
class RowPort_AVR_Optic : public RowPort
{
    private:
        const volatile unsigned char& DDR;      //Data Direction Register

    protected:
        volatile unsigned char& PORT;           //PORT register

    public:
        //The constructor initialization list is in .cpp
        RowPort_AVR_Optic(volatile unsigned char& DDRx, volatile unsigned char& PORTx);

        virtual void setActivePinLow(const uint8_t activePin); //activePin is a port mask
        virtual void setActivePinHigh(const uint8_t activePin);
};
#endif
