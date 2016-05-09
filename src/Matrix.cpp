#include "Matrix.h"

/*
scan every row of matrix one time
*/
void Matrix::scan()
{
    for (uint8_t i=0; i < rowCount; i++)
    {
        ptrsRows[i]->process(activeHigh);
    }
}
