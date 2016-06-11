#ifndef ROWBASE_H
#define ROWBASE_H
#include <Arduino.h>
#include <inttypes.h>
#include <Key.h>

/* RowBase is an abstract base class.
*/
class RowBase
{
    private:
        static const unsigned int DELAY_MICROSECONDS; //delay between each Row scan for debouncing
        Key *const *const ptrsKeys;         //array of Key pointers

        virtual void keyWasPressed();
    protected:
        uint8_t debounced;                  //bitwise, 1 means pressed, 0 means released

        void wait();
        void pressRelease(const uint16_t rowEnd, const uint8_t debouncedChanged);
    public:
        RowBase(Key *const ptrsKeys[]) : ptrsKeys(ptrsKeys), debounced(0) { }
        virtual void process();
        virtual uint8_t scan(uint16_t& rowEnd)=0;
        virtual uint8_t debounce(const uint8_t rowState, uint8_t& debounced)=0;
};
#endif
