#include <ncurses.h>
#include <iostream>
#include "character.h"
#include "map.h"
#include <cstdlib>
using namespace std;

int main()
{
    int ch, lost = 0;
    Map* map = new Map;
    Character player(map);
    initscr();
    keypad(stdscr, TRUE); 
    cbreak();
    ch = getch();
    halfdelay(1.5);
    noecho();
    
    ch = getch();
    while (lost == 0)
    {
	player.chDir(ch);
        lost = player.tick();
        ch = getch();
	refresh();
    }
    endwin();

    cout << "Your score was : " << player.score << endl;
    return 0;
}
