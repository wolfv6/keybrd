#ifndef CODE_NULL_H
#define CODE_NULL_H
#include <Arduino.h>
#include <Code.h>

/* Class Code_Null doesn't do anything.  It is useful for blank codes.
*/
class Code_Null: public Code
{
    public:
        virtual void press() {};
        virtual void release() {};
};
#endif
