#ifndef TETRIS_LIVELLO_H
#define TETRIS_LIVELLO_H

class livello {
protected:
    int lev;
    int timedif;
public:
    livello();
    void increase();
    bool checkforincrease(int ltot, int lnow);
    int getlevel();
    int gettimediff();


};

#endif //TETRIS_LIVELLO_H
