#include "menu.hpp"

int mainMenu(){
    int maxy, maxx;
    getmaxyx(stdscr, maxy, maxx);

    WINDOW *menu= newwin(NUM_OPTION_MAIN + 2, 20, maxy/2-NUM_OPTION_MAIN, maxx/2 - 8);
    box(menu, 0,0);
    refresh();
    wrefresh(menu);
    keypad(menu, true);

    int highlight=0;
    int choice;
    opzioni option[NUM_OPTION_MAIN]={{"   NEW GAME   "},{" LEADERBOARD  "}, {"     QUIT     "}};

    wrefresh(menu);

    bool flag = true;
    while (flag){
        for(int i = 0; i < NUM_OPTION_MAIN; i++){
            if (i == highlight){
                wattron(menu, A_STANDOUT);
            }
            mvwprintw(menu, i+1, 3, option[i].a);
            wattroff(menu,A_STANDOUT);
        }
        choice=wgetch(menu);
        switch (choice){
            case KEY_UP:
                highlight--;
                if (highlight == -1){
                    highlight=0;
                }
                break;
            case KEY_DOWN:
                highlight++;
                if (highlight== NUM_OPTION_MAIN){
                    highlight=0;
                }
                break;
            default:
                break;
        }
        if (choice == 10){
            flag = false;
        }
    }

    erase();

    //Return dell'opzione
    return highlight;
}

int saveMenu(){
    int maxy, maxx;
    getmaxyx(stdscr, maxy, maxx);

    WINDOW *menu= newwin(NUM_OPTION_SAVE + 2, 25, maxy/2-NUM_OPTION_SAVE, maxx/2 - (25/2));
    box(menu, 0,0);
    refresh();
    wrefresh(menu);
    keypad(menu, true);

    int highlight=0;
    int choice;
    opzioni option[NUM_OPTION_SAVE]={{"    SAVE SCORE    "},{"  RETURN TO MENU  "}};

    wrefresh(menu);

    bool flag = true;
    while (flag){
        for(int i = 0; i < NUM_OPTION_SAVE; i++){
            if (i == highlight){
                wattron(menu, A_STANDOUT);
            }
            mvwprintw(menu, i+1, 3, option[i].a);
            wattroff(menu,A_STANDOUT);
        }
        choice=wgetch(menu);
        switch (choice){
            case KEY_UP:
                highlight--;
                if (highlight == -1){
                    highlight=1;
                }
                break;
            case KEY_DOWN:
                highlight++;
                if (highlight== NUM_OPTION_SAVE){
                    highlight=0;
                }
                break;
            default:
                break;
        }
        //(Valore invio = 10)
        if (choice == 10){
            flag = false;
        }
    }
    erase();

    //return dell'opzione
    return highlight;
}

void insertNickname(char nickname[], int score){
    int maxy, maxx;
    getmaxyx(stdscr, maxy, maxx);

    int hbox = LINES/2;
    int wbox = COLS/2;
    WINDOW *nameSave= newwin(hbox, wbox, maxy/2-hbox/2, maxx/2-wbox/2);
    box(nameSave, 0,0);
    refresh();
    wrefresh(nameSave);

    int lungStringa = 20;
    char name[MAX_CHAR+1];
    for (int i = 0;i<MAX_CHAR;i++){
        name[i] = ' ';
    }
    name[MAX_CHAR] = '\0';

    int lungFrase = 18;
    bool invio = false;
    int c;
    int index=0;

    while(invio == false) {
        box(nameSave, 0,0);
        wrefresh(nameSave);
        refresh();
        mvwprintw(nameSave, 2, wbox / 2 - lungFrase / 2 - 3, "SAVE YOUR SCORE: %d", score);
        mvwprintw(nameSave, hbox / 2, wbox / 2 - lungStringa / 2 - MAX_CHAR/2, "Insert your nickname: %s", name);
        wrefresh(nameSave);
        wmove(nameSave, hbox / 2, wbox / 2 + lungStringa / 2 - MAX_CHAR/2 + index);
        noecho();
        c = wgetch(nameSave);
        mvwprintw(nameSave, hbox / 2 + 4, wbox / 2 - lungStringa / 2 - MAX_CHAR/2, "                                         ");
        
        if (c == 8) { //del
            if (index > 0) {
                index--;
                name[index] = ' ';
            }
        }
        else if(c == 10) { //invio
            if (index > 0) {
                invio = true;
            }
            else{
                mvwprintw(nameSave, hbox / 2 + 4, wbox / 2 - lungStringa / 2 - MAX_CHAR/2, "At least one character is needed");
            }
        }
        else{
            //    numeri da 0 a 9     maiuscole      minuscole
            if( (!((c>47 && c<58)||(c>64 && c<91)||(c>96 && c<123))) && index < MAX_CHAR){
                mvwprintw(nameSave, hbox / 2 + 4, wbox / 2 - lungStringa / 2 - MAX_CHAR/2, "Only alphanumeric characters are allowed");
            }
            else if(index > MAX_CHAR-1){
                mvwprintw(nameSave, hbox / 2 + 4, wbox / 2 - lungStringa / 2 - MAX_CHAR/2, "You can enter a maximum of %d characters", MAX_CHAR);
            }
            else{
                name[index] = c;
                index++;
            }
        }
        wrefresh(nameSave);
        refresh();
    }

    strcpy(nickname,name);
    refresh();

    erase();
}