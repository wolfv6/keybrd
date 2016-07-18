#ifndef DEBUG_H
#define DEBUG_H
#include <Arduino.h>
#include <LED.h>

class Debug
{
    private:
        unsigned long nextTime = 0;
        unsigned int scanCount = 0;

    public:
        void printMicrosecondsPerScan();        //print microseconds per scan every second
        void printScansPerSecond();             //print scans per second every second
        void wait_for_OS(LED& led, uint8_t seconds); //wait for OS to recongnize keyboard
};
#endif
