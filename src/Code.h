#ifndef CODE_H
#define CODE_H
#include "Key.h"

/* Code is an abstract base class.
Each Code object contains one USB scancode and sends the scancode to the computer.
*/
class Code : public Key
{
};
#endif
