#ifndef DEBUG_H
#define DEBUG_H
#include <Arduino.h>

class Debug
{
    private:
        unsigned long nextTime = 0;
        unsigned int scanCount = 0;

    public:
        void print_free_RAM();                  //print free SRAM, call this from setup()
        void print_microseconds_per_scan();     //print microseconds per scan every second
        void print_scans_per_second();          //print scans per second every second
};
#endif
