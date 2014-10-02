#include "character.h"
#include "map.h"
#include "window.h"

Character::Character(Map* theMap)
{
    map = theMap;
    tail = new Tail(15,14,0);
    tip = tail;
    dir = 's';
    eaten = 0;
    score = 0;
}

void Character::chDir(int inp)
{
    switch(inp)
    {
	    case 258 :
		if (dir != 'w' || score == 0)
		    dir = 's';
	    break;

	    case 259 :
		if (dir != 's' || score == 0)
		    dir = 'w';
	    break;

	    case 260 :
		if (dir != 'd' || score == 0)
		    dir = 'a';
	    break;

	    case 261 :
		if (dir != 'a' || score == 0)
		    dir = 'd';
	    break;

	    case 'w' :
	    case 'a' :
	    case 's' :
	    case 'd' :
		dir = inp;
	    break;
    }
}

int Character::tick()
{
    int destx = tail->x, desty = tail->y;
    char check;

    switch(dir)
    {
	    case 'w' :
		desty--;
	    break;

	    case 'a' :
		destx--;
	    break;

	    case 's' :
		desty++;
	    break;

	    case 'd' :
		destx++;
	    break;
    }

    check = map->getBlock(destx,desty);
    switch(check)
    {
	case 't' :
	    return 1;
	break;

	case 'o' :
	    tail = new Tail(destx, desty, tail);
	    map->addTail(tail);
	    tip = tip->next;
	    map->removeTail(tip->rest);
	    delete tip->rest;
	break;

	case 'f' :
	    tail = new Tail(destx, desty, tail);
	    map->addTail(tail);
	    map->addFood();
	    score++;
	break;
    }
    return 0;
}

Character::~Character()
{
    delete tail;
}
