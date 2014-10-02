#include "tail.h"

Tail::Tail(int xPos, int yPos, Tail* prev)
{
    x = xPos;
    y = yPos;
    rest = prev;
    next = 0;

    if (rest != 0)
	rest->next = this;
}

Tail::~Tail()
{
    delete rest;
    if (next != 0)
    {
	next->rest = 0;
    }
}

char Tail::getSymb()
{
    return 't';
}
