#ifndef __FOOD_H__
#define __FOOD_H__ 
#include "object.h"

struct Food : public Object
{
    Food(int xPos, int yPos);
    char getSymb();
};

#endif
