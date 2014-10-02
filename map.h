#ifndef __MAP_H__
#define __MAP_H__ 
#include "object.h"
#include "tail.h"
struct Xwindow;

struct Map
{
    Object*** blocks;
    Xwindow* display;
    int freeblocks;

    Map();
    char getBlock(int x, int y);
    void addTail(Tail*);
    void removeTail(Tail*);
    void addFood();
};

#endif
