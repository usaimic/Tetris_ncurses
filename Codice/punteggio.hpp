#ifndef TETRIS_PUNTEGGIO_H
#define TETRIS_PUNTEGGIO_H
#define PLINEA 100
#define BONUS 100

class punteggio {
protected:
    int score;

public:
    punteggio();
    void aumenta(int nlinee);
    int getscore();
    

};

#endif //TETRIS_PUNTEGGIO_H
