#include "food.h"

Food::Food(int xPos, int yPos)
{
    x = xPos;
    y = yPos;
}

char Food::getSymb()
{
    return 'f';
}
