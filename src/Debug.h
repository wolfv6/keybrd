#ifndef DEBUG_H
#define DEBUG_H
#include <Arduino.h>
#include <LEDInterface.h>

class Debug
{
    public:
        void printMicrosecondsPerScan();        //print microseconds per scan every second
        void printScansPerSecond();             //print scans per second every second
        void wait_for_OS(LEDInterface& led, uint8_t seconds); //wait for OS to recongnize keyboard
};
#endif
