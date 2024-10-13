#ifndef CARTELLAGIOCO_MENU_H
#define CARTELLAGIOCO_MENU_H

#include <curses.h>
#include <iostream>
#include <cstring>
using namespace std;

#define NUM_OPTION_MAIN 3
#define NUM_OPTION_SAVE 2
#define MAX_CHAR 20

struct opzioni
{
    char a[20];
};

int mainMenu();
int saveMenu();
void insertNickname(char nickname[], int score);
#endif //CARTELLAGIOCO_MENU_H
