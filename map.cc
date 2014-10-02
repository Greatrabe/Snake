#include "map.h"
#include "window.h"
#include "object.h"
#include "food.h"
#include <cstdlib>
#include <ctime>

Map::Map()
{
    int i, j;

    display = new Xwindow(300,300);
    blocks = new Object**[30];
    for (i = 0; i < 30; i++)
    {
	blocks[i] = new Object*[30];
	for (j = 0; j < 30; j++)
	{
	    blocks[i][j] = 0;
	}
    }
    freeblocks = 900;
    srand(time(NULL));	
    addFood();
}

char Map::getBlock(int x, int y)
{

    if (x >=0 && x < 30 && y >= 0 && y < 30)
    {
        if (blocks[x][y] != 0)
	    return blocks[x][y]->getSymb();
	else
	    return 'o';
    }
    else
	return 't';
}

void Map::addTail(Tail* tail)
{
    delete blocks[tail->x][tail->y];
    blocks[tail->x][tail->y] = tail;
    display->drawBlock(tail->x, tail->y, 1);
    freeblocks--;
}

void Map::removeTail(Tail* tail)
{ 
    blocks[tail->x][tail->y] = 0;
    display->drawBlock(tail->x, tail->y, 0); 
    freeblocks++;
}

void Map::addFood()
{
    int i=0, j=0, count = rand() % freeblocks;

    while (count != 0 || blocks[i][j] != 0)
    {
	if (blocks[i][j] == 0)
	{
	    count--;
	}

	if (count != 0)
	{
	    if (j == 29)
	    {
	        j = 0;
	        i++;
	    }
	    else
	    {
	        j++;
	    }
	}
    }

    blocks[i][j] = new Food(i,j);
    display->drawBlock(i, j, 7); 
}

//Needs destructor
