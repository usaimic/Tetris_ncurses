#include "graphic.hpp"
#include <curses.h>

using namespace std;

void intro(){
    int maxx,maxy;
    getmaxyx(stdscr,maxy,maxx);

    int hbox = LINES;
    int wbox = COLS;
    WINDOW *intro = newwin(hbox, wbox, 0,0);
    box(intro,0,0);
    refresh();
    wrefresh(intro);

    int lung = 45;
    int i = hbox/5;

    mvwprintw(intro,i  ,wbox/2-lung/2,"######## ###### ######## ####### ### #######");
    mvwprintw(intro,i+1,wbox/2-lung/2,"######## ###### ######## ####### ### #######");
    mvwprintw(intro,i+2,wbox/2-lung/2,"   ##    ##        ##    ##   ## ### ##     ");
    mvwprintw(intro,i+3,wbox/2-lung/2,"   ##    ##        ##    ##   ## ### ##     ");
    mvwprintw(intro,i+4,wbox/2-lung/2,"   ##    #####     ##    ####### ### #######");
    mvwprintw(intro,i+5,wbox/2-lung/2,"   ##    #####     ##    ## ##   ### #######");
    mvwprintw(intro,i+6,wbox/2-lung/2,"   ##    ##        ##    ##  ##  ###      ##");
    mvwprintw(intro,i+7,wbox/2-lung/2,"   ##    ##        ##    ##   ## ###      ##");
    mvwprintw(intro,i+8,wbox/2-lung/2,"   ##    #####     ##    ##   ## ### #######");
    mvwprintw(intro,i+9,wbox/2-lung/2,"   ##    #####     ##    ##   ## ### #######");

    refresh();
    wrefresh(intro);

    int lung2 = 22;
    mvwprintw(intro,i+14,wbox/2-lung2/2,"PRESS ANY KEY TO START ");
    refresh();
    wrefresh(intro);

    getch();
    erase();
}

void outro(){
    int maxx,maxy;
    getmaxyx(stdscr,maxy,maxx);

    int hbox = LINES;
    int wbox = COLS;
    WINDOW *outro = newwin(hbox, wbox, 0,0);
    box(outro,0,0);
    refresh();
    wrefresh(outro);

    int lung = 89;
    int i = hbox/5;

    mvwprintw(outro,i  ,wbox/2-lung/2,"######## ####### ###       ### #######         ########## ###        ### ####### #######");
    mvwprintw(outro,i+1,wbox/2-lung/2,"######## ####### ####     #### #######         ########## ###        ### ####### #######");
    mvwprintw(outro,i+2,wbox/2-lung/2,"##       ##   ## ## ##   ## ## ##              ##      ##  ###      ###  ##      ##   ##");
    mvwprintw(outro,i+3,wbox/2-lung/2,"##       ##   ## ##  ## ##  ## ##              ##      ##  ###      ###  ##      ##   ##");
    mvwprintw(outro,i+4,wbox/2-lung/2,"##  #### ##   ## ##   ###   ## #####           ##      ##   ###    ###   #####   #######");
    mvwprintw(outro,i+5,wbox/2-lung/2,"##  #### ####### ##         ## #####           ##      ##   ###    ###   #####   ## ##  ");
    mvwprintw(outro,i+6,wbox/2-lung/2,"##    ## ####### ##         ## ##              ##      ##    ###  ###    ##      ##  ## ");
    mvwprintw(outro,i+7,wbox/2-lung/2,"##    ## ##   ## ##         ## ##              ##      ##    ###  ###    ##      ##   ##");
    mvwprintw(outro,i+8,wbox/2-lung/2,"######## ##   ## ##         ## #######         ##########     ######     ####### ##   ##");
    mvwprintw(outro,i+9,wbox/2-lung/2,"######## ##   ## ##         ## #######         ##########     ######     ####### ##   ##");

    refresh();
    wrefresh(outro);

    int lung2 = 22;
    mvwprintw(outro,i+14,wbox/2-lung2/2,"PRESS [ENTER] TO CONTINUE ");
    refresh();
    wrefresh(outro);


    int inp = getch();
    while(inp!=10)
        inp = getch();
    erase();
}