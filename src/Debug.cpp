#include "Debug.h"

void Debug::printMicrosecondsPerScan()
{
    static unsigned long nextTime = 0;
    static unsigned int scanCount = 0;

    if (millis() >= nextTime)
    {
        Keyboard.print(1000000/scanCount);      //print microseconds per scan
        Keyboard.write(',');
        scanCount = 0;
        nextTime = millis() + 1000;             //print every second
    }
    scanCount++;
}
void Debug::printScansPerSecond()
{
    static unsigned long nextTime = 0;
    static unsigned int scanCount = 0;

    if (millis() >= nextTime)
    {
        Keyboard.print(scanCount);              //print scans per second
        Keyboard.write(',');
        scanCount = 0;
        nextTime = millis() + 1000;             //print every second
    }
    scanCount++;
}

//Sometimes OS takes 6 seconds to recongnize keyboard.
//wait_for_OS() will blink LED and count up once per second for specified number of seconds.
void Debug::wait_for_OS(LEDInterface& led, const uint8_t seconds)
{
    for (uint8_t elapsed = 0; elapsed < seconds; elapsed++)
    {
        //print seconds elapsed
        Keyboard.print(elapsed);
        Keyboard.print(F(" "));

        //blink LED
        led.on();
        delay(500);
        led.off();
        delay(500);
    }
}
