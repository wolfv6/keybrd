#include "Code_AutoShift.h"

bool Code_AutoShift::isShifted() const
{
    //if a shift key is pressed return true else return false
    for (uint8_t i = 0; i < shiftCount; i++)
    {
        if (ptrsShifts[i]->isPressed())
        {
            return true;
        }
    }
    return false;
}

void Code_AutoShift::releaseAllShifts() const
{
    for (uint8_t i = 0; i < shiftCount; i++)
    {
        ptrsShifts[i]->unpress();
    }
}

void Code_AutoShift::restoreAllShifts() const
{
    for (uint8_t i = 0; i < shiftCount; i++)
    {
        ptrsShifts[i]->restorePressed();
    }
}
