#include "punteggio.hpp"

punteggio::punteggio (){
    this->score=0;
}

void punteggio::aumenta(int nlinee){
    this->score= this->score + PLINEA*nlinee+ (nlinee-1)*BONUS;
}

int punteggio::getscore(){
    return this->score;
}