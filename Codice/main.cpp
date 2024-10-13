/* AUTORI E MEMBRI DEL GRUPPO:
 * 
 * Antonio Alati
 * - Email: antonio.alati@studio.unibo.it
 * - Num. Matricola: 0001126541
 *
 * Michele Palma
 * - Email: michele.palma2@stu.unibo.it
 * - Num. Matricola: 0001142598
 *
 * Michael Usai
 * - Email: michael.usai@studio.unibo.it
 * - Num. Matricola: 0001114611
 *
 * Manuele Lelli
 * - Email: manuele.lelli@studio.unibo.it
 * - Num. Matricola: 0001030993
 */
 
#include <curses.h>
#include "Score.hpp"
#include "graphic.hpp"
#include "menu.hpp"
#include "tabella.hpp"

#define POS_X 3
#define POS_Y 1

/* In Main.cpp vengono chiamate e gestite
 * tutte le schermate. Le schermate sono:
 * - TITOLO
 * - MENU INIZIALE
 * - SESSIONE DI GIOCO
 * - GAME OVER
 * - MENU DI SALVATAGGIO
 * - INSERIMENTO NOME
 */

using namespace std;

void mostraClassifica(PlayerScorePtr head){
    head = NULL;
    head = readFromFile(head);
    displayScores(head); //score.cpp
}

int main() {
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    keypad(stdscr, TRUE);

    bool esc = false;
    int save = -1;
    int opzione = -1;
    int score = -1;
    int sec=0;
    int min=0;
    char nickname[20];
    PlayerScorePtr head;

    // --== TITOLO ==--
    intro(); //graphic.cpp

    while(!esc){
        // --== MENU INIZIALE ==--
        opzione = mainMenu(); //menu.cpp

        //Nuova partita
        if(opzione == 0) {
            tabella gb = tabella(POS_X, POS_Y);

            // --== SESSIONE DI GIOCO ==--
            score = gb.start(); //tabella.cpp

            // --== GAME OVER ==--
            outro(); //graphic.cpp

            // --== MENU DI SALVATAGGIO ==--
            save = saveMenu(); //menu.cpp

            //Salva
            if (save == 0) {
                min = gb.getminutes();
                sec = gb.getseconds();

                // --== INSERIMENTO NOME ==--
                insertNickname(nickname,score); //menu.cpp

                addplayer(nickname,score,min,sec);
            }
        }

        //Classifica
        else if(opzione == 1) {
            erase();

            // --== CLASSIFICA ==--
            mostraClassifica(head); //main.cpp
        }

        //Esci
        else if(opzione == 2){
            esc = true;
        }
    }

    endwin();
    return 0;
}