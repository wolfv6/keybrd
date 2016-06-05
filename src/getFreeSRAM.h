// getFreeSRAM.h copied from
// http://andybrown.me.uk/2011/01/01/debugging-avr-dynamic-memory-allocation/
/*
 * memdebug.h
 *
 *  Created on: 15 Dec 2010
 *      Author: Andy Brown
 *
 *  Use without attribution is permitted provided that this
 *  header remains intact and that these terms and conditions
 *  are followed:
 *
 *  http://andybrown.me.uk/ws/terms-and-conditions
 */

#include <inttypes.h>

extern unsigned int __bss_end;
extern unsigned int __heap_start;
extern void *__brkval;

//measure and return amount of free SRAM
/*
uint16_t getFreeSRAM()
{
    uint8_t newVariable;
    // if heap is empty, use bss as start memory address
    if ((uint16_t)__brkval == 0)
    {
        return (((uint16_t)&newVariable) - ((uint16_t)&__bss_end));
    }
    // else use heap end as the start of the memory address
    else
    {
        return (((uint16_t)&newVariable) - ((uint16_t)__brkval));
    }
};
*/
// uint32_t for Teensy LC
uint32_t getFreeSRAM()
{
    uint8_t newVariable;
    // if heap is empty, use bss as start memory address
    if ((uint32_t)__brkval == 0)
    {
        return (((uint32_t)&newVariable) - ((uint32_t)&__bss_end));
    }
    // else use heap end as the start of the memory address
    else
    {
        return (((uint32_t)&newVariable) - ((uint32_t)__brkval));
    }
};
