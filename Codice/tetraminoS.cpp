#include "tetraminoS.hpp"

tetraminoS::tetraminoS(int num) {
    switch(num){
        case 1: // T shape
            blocchi[0].y=1; blocchi[0].x=1;
            blocchi[1].y=1; blocchi[1].x=0;
            blocchi[2].y=1; blocchi[2].x=2;
            blocchi[3].y=0; blocchi[3].x=1;
            dim=3;
            c = '-';
            break;
        case 2: // Z shape 1
            blocchi[0].y=1; blocchi[0].x=1;
            blocchi[1].y=0; blocchi[1].x=0;
            blocchi[2].y=0; blocchi[2].x=1;
            blocchi[3].y=1; blocchi[3].x=2;
            dim=3;
            c = '/';
            break;
        case 3: // Z shape 2
            blocchi[0].y=1; blocchi[0].x=1;
            blocchi[1].y=0; blocchi[1].x=2;
            blocchi[2].y=0; blocchi[2].x=1;
            blocchi[3].y=1; blocchi[3].x=0;
            dim=3;
            c = '\\';
            break;
        case 4: // L shape 1
            blocchi[0].y=1; blocchi[0].x=1;
            blocchi[1].y=0; blocchi[1].x=0;
            blocchi[2].y=1; blocchi[2].x=0;
            blocchi[3].y=1; blocchi[3].x=2;
            dim=3;
            c = '>';
            break;
        case 5: // L shape 2
            blocchi[0].y=1; blocchi[0].x=1;
            blocchi[1].y=0; blocchi[1].x=2;
            blocchi[2].y=1; blocchi[2].x=0;
            blocchi[3].y=1; blocchi[3].x=2;
            dim=3;
            c = '<';
            break;
        case 6: // [] shape
            blocchi[0].y=0; blocchi[0].x=0;
            blocchi[1].y=0; blocchi[1].x=1;
            blocchi[2].y=1; blocchi[2].x=0;
            blocchi[3].y=1; blocchi[3].x=1;
            dim=2;
            c = ' ';
            break;
        case 7: // | shape
            blocchi[0].y=1; blocchi[0].x=0;
            blocchi[1].y=1; blocchi[1].x=1;
            blocchi[2].y=1; blocchi[2].x=2;
            blocchi[3].y=1; blocchi[3].x=3;
            dim=4;
            c = '|';
            break;
    }
}

char tetraminoS::getChar(){ return c; }

block tetraminoS::getBlock(int i){ return blocchi[i]; }

int tetraminoS::getDim(){ return dim; }

void tetraminoS::ruotaOrario() {
    block temp [Nblocks];
    for(int i=0; i<Nblocks; i++)
        temp[i] = blocchi[i];

    for(int i=0; i<Nblocks; i++) {
        blocchi[i].y = temp[i].x;
        blocchi[i].x = dim-1-temp[i].y;
    }
}

void tetraminoS::ruotaAntiOrario() {
    block temp [Nblocks];
    for(int i=0; i<Nblocks; i++)
        temp[i] = blocchi[i];

    for(int i=0; i<Nblocks; i++) {
        blocchi[i].x = temp[i].y;
        blocchi[i].y = dim-1-temp[i].x;
    }
}