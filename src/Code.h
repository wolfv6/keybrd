#ifndef CODE_H
#define CODE_H
#include "Key.h"

/* Code is an interface class
It's derived concrete classes send press and release USB scancodes to the computer.
*/
class Code : public Key
{
};
#endif
