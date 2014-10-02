#ifndef __CHARACTER_H__
#define __CHARACTER_H__ 
#include "tail.h"

struct Map;

struct Character
{
    Tail* tail;
    Tail* tip;
    Map* map;
    int dir, eaten, score;

    Character(Map* theMap);
    void chDir(int inp);
    int tick();
    ~Character();
};

#endif
