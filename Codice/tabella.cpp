#include <curses.h>
#include <iostream>
#include <ctime>
#include "tabella.hpp"
#include "punteggio.hpp"
#include "livello.hpp"
using namespace std;

#define OFFSET_X_RIGHT 10
#define OFFSET_Y_RIGHT 1
#define OFFSET_X_TABLE 2
#define OFFSET_Y_TABLE 3

tabella::tabella(int pos_x, int pos_y){
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->start_time=time(0);
    for(int y=0; y<this->sizeY; y++)
        for(int x=0; x<this->sizeX; x++)
                this->matrice[y][x] = '.';
}

void tabella::updateMat(tetraminoS tet){
    for(int i=0; i<Nblocks; i++) {
        int by = tet.getBlock(i).y;
        int bx = tet.getBlock(i).x;
        matrice[by+cy][bx+cx] = tet.getChar();
    }
}

bool tabella::sposta(int new_cy, int new_cx, tetraminoS tet){
    bool possible = true;
    int i=0;
    while(i<Nblocks && possible) {
        int by = tet.getBlock(i).y;
        int bx = tet.getBlock(i).x;
        if(
                ((new_cy+by) > (this->sizeY-1)) ||
                ((new_cx+bx) > (this->sizeX-1)) ||
                ((new_cy+by) < 0) ||
                ((new_cx+bx) < 0) ||
                (matrice[new_cy+by][new_cx+bx]!='.')
                ) possible = false;
        i++;
    }

    return possible;
}

bool tabella::ruota(tetraminoS tet, bool sensoOrario){
    if(sensoOrario) tet.ruotaOrario();
    else            tet.ruotaAntiOrario();

    bool possible = true;
    int i=0;
    while(i<Nblocks && possible) {
        int by = tet.getBlock(i).y;
        int bx = tet.getBlock(i).x;
        if(
            ((cy+by) > (this->sizeY-1)) ||
            ((cx+bx) > (this->sizeX-1)) ||
            ((cy+by) < 0) ||
            ((cx+bx) < 0) ||
            (matrice[cy+by][cx+bx]!='.')
        ) possible = false;
        i++;
    }

    return possible;
}

int tabella::controllaLinee(int dim){
    int lineeEliminate = 0;
    for(int i=cy; i<cy+dim && i<sizeY; i++){
        bool EmptyBlock = false;

        for(int j=0; j<sizeX; j++){
            if(matrice[i][j]=='.')
                EmptyBlock = true;
        }

        if(!EmptyBlock){
            for(int z=i-1; z>=0; z--)
                for(int x=0; x<sizeX; x++)
                    matrice[z+1][x] = matrice[z][x];

            lineeEliminate++;
        }
    }
    return lineeEliminate;
}

void tabella::printTetramino(tetraminoS tet, char c){
    for(int i=0; i<Nblocks; i++) {
        int by = tet.getBlock(i).y;
        int bx = tet.getBlock(i).x;
        if(c=='.')
            mvprintw(pos_y+OFFSET_Y_TABLE+(cy+by), pos_x+OFFSET_X_TABLE+(cx+bx)*3, " . ");
        else
            mvprintw(pos_y+OFFSET_Y_TABLE+(cy+by), pos_x+OFFSET_X_TABLE+(cx+bx)*3, "[%c]", c);
    }
}

void tabella::printNextTetramino(tetraminoS tet, char c){
    for(int i=0; i<Nblocks; i++) {
        int by = tet.getBlock(i).y;
        int bx = tet.getBlock(i).x;
        if(c=='.')
            mvprintw(pos_y+OFFSET_Y_RIGHT+9+by, pos_x+sizeX*3+OFFSET_X_TABLE+OFFSET_X_RIGHT+bx*3, "   ");
        else
            mvprintw(pos_y+OFFSET_Y_RIGHT+9+by, pos_x+sizeX*3+OFFSET_X_TABLE+OFFSET_X_RIGHT+bx*3, "[%c]", c);
    }
}

void tabella::printTable(){
    move(pos_y+2,pos_x+2);
    for(int x=0; x<this->sizeX; x++) { printw("___"); }

    for (int y = 0; y < this->sizeY; y++){
        move(pos_y+y+3,pos_x+2);
        for(int x=0; x<this->sizeX; x++) {
            if(matrice[y][x]=='.') {
                printw(" . ");
            }else{
                printw("[%c]",matrice[y][x]);
            }
        }
    }
}

void tabella::printScore(int score) {
    move(pos_y+OFFSET_Y_RIGHT+1, pos_x+sizeX*3+OFFSET_X_TABLE+OFFSET_X_RIGHT);
    printw("%d",score);
}

void tabella::printLines(int lines) {
    move(pos_y+1,pos_x+2);
    for(int x=0; x<this->sizeX; x++) { printw("   "); }

    int lunghezzaLinee = 0;
    if(lines!=0) {
        int numero = lines;
        while (numero != 0) {
            numero /= 10;
            lunghezzaLinee++;
        }
    }else{
        lunghezzaLinee = 1;
    }
    mvprintw(pos_y+1, pos_x+2+(sizeX*3)/2-3-lunghezzaLinee/2, "LINES: %d", lines);
}

void tabella::printLevel(int level) {
    move(pos_y+OFFSET_Y_RIGHT+4, pos_x+sizeX*3+OFFSET_X_TABLE+OFFSET_X_RIGHT);
    printw("%d",level);
}

void tabella::printBox(){
    refresh();
    WINDOW *menu = newwin(sizeY+4, sizeX*3+2, pos_y, pos_x+1);
    box(menu, 0,0);
    wrefresh(menu);
}

void tabella::manageInp(bool &newTet, bool &movement, int inp, tetraminoS &tet, bool &used) {
        keypad(stdscr,true);
    if(inp==83 || inp==115 || inp==258){ // tasto s/S - FRECCIA GIU'
        bool esegui = sposta(cy+1, cx, tet);
        if(esegui) {
            printTetramino(tet, '.');
            cy++;
            movement = true;
        }else{
            newTet = true;
            used = false;
        }
    }else if(inp==65 || inp==97 || inp==260){  // tasto a/A - FRECCIA SINISTRA
        bool esegui = sposta(cy, cx-1, tet);
        if(esegui) {
            printTetramino(tet, '.');
            cx--;
            movement = true;
        }
    }else if(inp==68 || inp==100 || inp==261){ // tasto d/D - FRECCIA DESTRA
        bool esegui = sposta(cy, cx+1, tet);
        if(esegui) {
            printTetramino(tet, '.');
            cx++;
            movement = true;
        }
    }else if(inp==69 || inp==101 || inp==259){ // tasto e/E - FRECCIA SU
        bool esegui = ruota(tet, true);
        if(esegui) {
            printTetramino(tet, '.');
            tet.ruotaOrario();
            movement = true;
        }
    }else if(inp==81 || inp==113){ // tasto q/Q
        bool esegui = ruota(tet, false);
        if(esegui) {
            printTetramino(tet, '.');
            tet.ruotaAntiOrario();
            movement = true;
        }
    }
}

int tabella:: getminutes() {
    time_t timenow=time(0);
    time_t diff= timenow-this->start_time;
    return diff/60;
}

int tabella:: getseconds() {
    time_t timenow=time(0);
    time_t diff= timenow-this->start_time;
    return diff%60;
}

void tabella::printTime() {
    move(pos_y+OFFSET_Y_RIGHT+16, pos_x+sizeX*3+OFFSET_X_TABLE+OFFSET_X_RIGHT);

    int sec = getseconds();
    if(sec<10)
        printw("%d:0%d",getminutes(),sec);
    else
        printw("%d:%d",getminutes(),sec);
}

int tabella::start(){
    bool used = 0; //variabile per utilizzo dello scambio del tetramino
    srand(time(0));

    int numTet = rand()%7+1;
    tetraminoS tet = tetraminoS(numTet);
    if(numTet!=7) {
        cx = sizeX / 2 - tet.getDim() / 2;
        cy = 0;
    }else {
        cx = sizeX / 2 - tet.getDim() / 2;
        cy = -1;
    }

    numTet = rand()%7+1;
    tetraminoS next = tetraminoS(numTet);

    punteggio punti=punteggio();
    livello level=livello();
    bool GameOver = false;

    mvprintw(pos_y+OFFSET_Y_RIGHT   , pos_x+sizeX*3+OFFSET_X_TABLE+OFFSET_X_RIGHT ,"SCORE");
    mvprintw(pos_y+OFFSET_Y_RIGHT+3 , pos_x+sizeX*3+OFFSET_X_TABLE+OFFSET_X_RIGHT ,"LEVEL");
    mvprintw(pos_y+OFFSET_Y_RIGHT+8 , pos_x+sizeX*3+OFFSET_X_TABLE+OFFSET_X_RIGHT ,"NEXT");
    mvprintw(pos_y+OFFSET_Y_RIGHT+15, pos_x+sizeX*3+OFFSET_X_TABLE+OFFSET_X_RIGHT ,"TIME");

    printScore(punti.getscore());
    printLevel(level.getlevel());
    printNextTetramino(next, next.getChar());
    printTime();
    printBox();

    printTable();
    printLines(0);
    printTetramino(tet, tet.getChar());

    nodelay(stdscr, TRUE);
    int inp = getch();
    clock_t t1=clock();  //acquisizione tempo inizio
    clock_t t2;
    int lineeeliminate;
    int lineetot=0;

    while(!GameOver){
        bool newTet = false;
        bool movement = false;
        printTime();
        refresh();
        t2=clock();

        //Movimento per effetto della gravità
        if(t2-t1 > level.gettimediff()){
            t1=t2;
            manageInp(newTet, movement, 115, tet, used);
        }

        //Input del giocatore
        manageInp(newTet, movement, inp, tet, used);

        //Gestione delle modifiche del tetramino
        if(movement){
            printTetramino(tet, tet.getChar());
            refresh();
        }else if(newTet){
            printNextTetramino(next, '.');
            updateMat(tet);

            //Controllo per delle linee da cancellare
            lineeeliminate= controllaLinee((tet.getDim()));
            if(lineeeliminate!=0) {
                punti.aumenta(lineeeliminate);
                if(level.checkforincrease(lineetot,lineeeliminate) &&lineetot!=0)
                    level.increase();
                lineetot+=lineeeliminate;
            }

            //Genero il nuovo tetramino e ristampo tutta la tabella
            tet = next;
            if(numTet!=7) {
                cx = sizeX / 2 - tet.getDim() / 2;
                cy = 0;
            }else {
                cx = sizeX / 2 - tet.getDim() / 2;
                cy = -1;
            }

            numTet = rand()%7+1;
            next = tetraminoS(numTet);

            //Controllo che posso continuare a giocare
            bool esegui = sposta(cy, cx, tet);
            if(!esegui) {GameOver=true;}

            printScore(punti.getscore());
            printLevel(level.getlevel());
            printNextTetramino(next, next.getChar());
            printBox();
            printTable();
            printLines(lineetot);
            printTetramino(tet, tet.getChar());
            refresh();
        }

        inp = getch();
    }
    nodelay(stdscr, FALSE);
    erase();

    return punti.getscore();
}