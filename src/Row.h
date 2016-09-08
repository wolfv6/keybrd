#ifndef ROW_H
#define ROW_H

#include <Arduino.h>
#include <inttypes.h>
#include <config_keybrd.h>
#include <Key.h>
#include <ScannerInterface.h>
#include <Debouncer_Samples.h>

/*
strobePin has one of two formats:
 * if refScanner a Scanner_uC, then strobePin is an Arduino pin number connected to this row
 * if refScanner a Scanner_IOE, then strobePin is bitwise, 1 indicating IC pin connected to this row
*/
class Row
{
    private:
        virtual void keyWasPressed();
    protected:
        void send(const uint8_t readPinCount, const read_pins_t debouncedChanged);
        ScannerInterface& refScanner;
        const uint8_t strobePin;                //pin connected to this row (details above)
    private:
        Key *const *const ptrsKeys;             //array of Key pointers
    protected:
        const uint8_t readPinCount;             //number of read pins
        Debouncer_Samples debouncer;
        read_pins_t debounced;      //bitwise state of keys after debouncing, 1=pressed, 0=released
    public:
        Row(ScannerInterface& refScanner, const uint8_t strobePin,
                Key* const ptrsKeys[], const uint8_t readPinCount);
        virtual void process();
};
#endif
