#ifndef ROW_H
#define ROW_H

#include <Arduino.h>
#include <inttypes.h>
#include "config_keybrd.h"
#include "Key.h"
#include "ScannerInterface.h"
#include "Debouncer_Samples.h"
#include "Debouncer_Not.h"

/*
strobePin has one of two formats:
 * if strobe pin is on uC (strobe for Scanner_uC or Scanner_ShiftRegsRead),
    then strobePin is an Arduino pin number connected to this row.
 * if strobe pin is on I/O expander (strobe for Scanner_IOE), then strobePin is bit pattern,
    1 indicating the I/O expander pin connected to this row
*/
class Row
{
    private:
        virtual void keyWasPressed();
    protected:
        void send(const uint8_t keyCount, const read_pins_t debouncedChanged);
        ScannerInterface& refScanner;
        const uint8_t strobePin;                //pin connected to this row (details above)
    private:
        Key *const *const ptrsKeys;             //array of Key pointers
    protected:
        const uint8_t keyCount;                 //number of read pins
        //Debouncer_Samples debouncer;
        Debouncer_Not debouncer; //todo restore Debouncer_Samples after testing
        read_pins_t debounced; //bit pattern, state of keys after debouncing, 1=pressed, 0=released
    public:
        Row(ScannerInterface& refScanner, const uint8_t strobePin,
            Key* const ptrsKeys[], const uint8_t keyCount);
        virtual void process();
};
#endif
