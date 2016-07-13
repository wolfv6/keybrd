#include "ReadPort.h"

uint8_t ReadPort::getColPins()
{
    return readPins;
}

uint8_t ReadPort::getPortState()
{
    return portState;
}
