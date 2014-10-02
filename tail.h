#ifndef __TAIL_H__
#define __TAIL_H__ 
#include "object.h"

struct Tail : public Object
{
    Tail* next;
    Tail* rest;

    Tail(int xPos, int yPos, Tail* prev);
    ~Tail();
    char getSymb();
};

#endif
