#include "Debug.h"
#include "getFreeSRAM.h"

void Debug::print_free_RAM()
{
    delay(1000);                                //give OS time to find USB
    Keyboard.print(F("Free SRAM = "));
    Keyboard.println( getFreeSRAM() );
}

void Debug::print_microseconds_per_scan()
{
    if (millis() >= nextTime)
    {
        Keyboard.print(1000000/scanCount);      //print microseconds per scan
        Keyboard.write(',');
        scanCount = 0;
        nextTime = millis() + 1000;             //print every second
    }
    scanCount++;
}
void Debug::print_scans_per_second()
{
    if (millis() >= nextTime)
    {
        Keyboard.print(scanCount);              //print scans per second
        Keyboard.write(',');
        scanCount = 0;
        nextTime = millis() + 1000;             //print every second
    }
    scanCount++;
}
