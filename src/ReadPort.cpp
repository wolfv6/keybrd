#include "ReadPort.h"

uint8_t ReadPort::getColPins()
{
    return readPins;
}

uint8_t ReadPort::getPortState()
{
//todo Keyboard.print(" portState=");
//Keyboard.print(portState);
    return portState;
}
