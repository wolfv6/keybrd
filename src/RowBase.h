#ifndef ROWBASE_H
#define ROWBASE_H
#include <Arduino.h>
#include <inttypes.h>
#include <Key.h>
#include <RowPort.h>
#include <ColPort.h>

/* RowBase is an abstract base class.
*/
class RowBase
{
    private:
        static const unsigned int DELAY_MICROSECONDS; //delay between each Row scan for debouncing
        Key *const *const ptrsKeys;         //array of Key pointers

        RowPort &refRowPort;                //this row's IC port
        const uint8_t rowPin;               //bitwise, 1 indicates IC pin connected to this row

        ColPort *const *const ptrsColPorts; //array of column ports
        const uint8_t colPortCount;

        void wait();
        void scan(const bool activeHigh);
        uint8_t getRowState(uint16_t& rowEnd, const bool activeHigh);
        virtual uint8_t debounce(const uint8_t rowState)=0;
        void pressRelease(const uint16_t rowEnd, const uint8_t debouncedChanged);
        virtual void keyWasPressed();
    protected:
        uint8_t debounced;                  //bitwise, 1 means pressed, 0 means released
    public:
        RowBase( RowPort &refRowPort, const uint8_t rowPin,
            ColPort *const ptrsColPorts[], const uint8_t colPortCount,
            Key *const ptrsKeys[])
            : ptrsKeys(ptrsKeys), refRowPort(refRowPort), rowPin(rowPin),
              ptrsColPorts(ptrsColPorts), colPortCount(colPortCount),
              debounced(0) { }
        //Key* getPtrKey(uint8_t col) const; todo delete, no longer needed 5/31/16
        void process(const bool activeHigh);
};
#endif
