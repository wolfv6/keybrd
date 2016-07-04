#ifndef ROWBASE_H
#define ROWBASE_H
#include <Arduino.h>
#include <inttypes.h>
#include <config_keybrd.h>
#include <Key.h>

/* RowBase is an abstract base class.
*/
class RowBase
{
    private:
        Key *const *const ptrsKeys;             //array of Key pointers
        virtual void keyWasPressed();
    protected:
        read_pins_t debounced;                  //bitwise, 1 means pressed, 0 means released
        void pressRelease(const read_pins_mask_t rowEnd, const read_pins_t debouncedChanged);
    public:
        RowBase(Key *const ptrsKeys[]) : ptrsKeys(ptrsKeys), debounced(0) { }
        virtual void process()=0;
};
#endif
