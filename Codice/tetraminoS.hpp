#ifndef TETRIS_TETRAMINOS_H
#define TETRIS_TETRAMINOS_H

#define Nblocks 4

struct block{
    int x;
    int y;
};

class tetraminoS {

protected:
    block blocchi[Nblocks];
    int dim;
    char c;

public:
    tetraminoS(int num);

    char getChar();
    block getBlock(int i);
    int getDim();

    void ruotaOrario();
    void ruotaAntiOrario();
};

#endif //TETRIS_TETRAMINOS_H