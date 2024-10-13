#include "livello.hpp"

livello::livello(){
    this->lev=1;
    this->timedif=500;
}

void livello::increase(){
    this->lev++;
    this->timedif=timedif-timedif/10;
}

bool livello::checkforincrease(int ltot, int lnow) {
    bool inc=false;
    for(int i=0; i<lnow; i++){
        if(( ltot+i)%10 == 0){
            inc=true;
        }
    }
    return inc;
}

int livello::getlevel(){
    return this->lev;
}

int livello::gettimediff(){
    return this->timedif;
}
