#ifndef ROWBASE_H
#define ROWBASE_H
#include <Arduino.h>
#include <inttypes.h>
#include <Key.h>

/* RowBase is an abstract base class.

Define and initilize DELAY_MICROSECONDS in sketch.
    const unsigned int RowBase::DELAY_MICROSECONDS = 0;
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
        virtual void process()=0;
};
#endif
