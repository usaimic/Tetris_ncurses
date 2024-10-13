#include "tetraminoS.hpp"
#include <ctime>
#ifndef TETRIS_TABELLA_H
#define TETRIS_TABELLA_H
#define X 10 //10
#define Y 20 //20

class tabella {

protected:
    char matrice[Y][X];
    int sizeX = X;
    int sizeY = Y;
    //Posizione della schermata
    int pos_x;
    int pos_y;
    //Posizione del cursore del tetramino
    int cx=0;
    int cy=0;
    time_t start_time;

public:
    tabella(int pos_x, int pos_y);
    void updateMat(tetraminoS tet);
    bool sposta(int new_cy, int new_cx, tetraminoS tet);
    bool ruota(tetraminoS tet, bool sensoOrario);
    int controllaLinee(int dim);
    void printTetramino(tetraminoS tet, char c);
    void printNextTetramino(tetraminoS tet, char c);
    void printTable();
    void printScore(int score);
    void printLines(int lines);
    void printLevel(int level);
    void printBox();
    void manageInp(bool &newTet, bool &movement, int inp, tetraminoS &tet, bool &used);
    int start();
    void printTime();
    int getminutes();
    int getseconds();
};

#endif //TETRIS_TABELLA_H
