#include "Score.hpp"
#include <cstring>
#include <iostream>
#include <fstream>
#include <curses.h>

using namespace std;
void addplayer(char nickname[], int score, int min, int sec) {
    char nomefile[MAX] = "score.txt";
    ofstream outputF(nomefile, ios::app);
    if (!outputF.is_open()) {
        cerr << "Impossibile aprire il file " << nomefile << " per la scrittura" << endl;
        return;
    }
    outputF << "\n";
    outputF << nickname << " " << score << " " << min << " " << sec;
    outputF.close();
}

PlayerScorePtr insertsorted(PlayerScorePtr head, char nickname[], int sc, int minu, int seco) {
    PlayerScorePtr tmp = new PlayerScore;
    strncpy(tmp->name, nickname,MAX);
    tmp->score = sc;
    tmp->min = minu;
    tmp->sec = seco;
    if (head == NULL || sc > head->score && (minu<=head->min && seco<=head->sec))
    {
        tmp->next = head;
        return tmp;
    }
    else
    {
        PlayerScorePtr current = head;
        PlayerScorePtr prev = NULL;
        while (current != NULL && sc < current->score)
        {
            prev = current;
            current = current->next;
        }
        while(current!=NULL && sc==current->score && minu*60+seco>=current->min*60+current->sec) {
            prev = current;
            current = current->next;
        }
        tmp->next = current;
        if (prev != NULL)
        {
            prev->next = tmp;
        }
        else
        {
            head = tmp;
        }
        return head;
    }
}

PlayerScorePtr readFromFile(PlayerScorePtr head) {
    char nomefile[MAX] = "score.txt";
    ifstream inputfile(nomefile, ios::in);
    if (!inputfile.is_open()) {
        cerr << "Impossibile aprire il file " << nomefile << endl;
        return head;
    }
    char nickname[MAX];
    int score = 0;
    int minutes=0;
    int seconds=0;
    while (!inputfile.eof()) {
        inputfile >> nickname;
        inputfile >> score;
        inputfile >> minutes;
        inputfile >> seconds;
        head = insertsorted(head, nickname, score,minutes,seconds);
    }
    inputfile.close();
    return head;
}

void displayScores(PlayerScorePtr head) {
    int row, col;
    getmaxyx(stdscr, row, col); // Ottieni le dimensioni dello schermo

    int offset = 0; // Offset per gestire lo scorrimento
    PlayerScorePtr current = head;
    int ch; //variabile d' input

    bool flag=false;
    while (!flag) {
        clear(); // Pulisce lo schermo

        // Calcola le coordinate per centrare orizzontalmente
        int start_col = (col - 50) / 2;

        mvprintw(0, start_col, "PRESS [Q] TO GO BACK");
        mvprintw(2, (col - 10) / 2, "LEADERBOARD:");

        // Calcola il numero massimo di righe visualizzabili
        int max_display_rows = row - 3; // Acquisisce la grandezza della schermata e sottrae 3 di margine

        // Trova l'elemento della lista da cui iniziare a visualizzare a ogni esecuzione del ciclo
        PlayerScorePtr temp = head;
        for (int i = 0; i < offset && temp != NULL; i++) {
            temp = temp->next;
        }

        // Stampa la classifica centrata
        int i = 0;
        int num = offset + 1; // Inizializza il numero di elementi da visualizzare
        while (temp != NULL && i < max_display_rows) {
            if (start_col < 0) start_col = 0;

            if (temp == current) {
                attron(A_REVERSE); // Evidenzia la riga corrente
            }

            if(num<10)
                mvprintw(i + 4, start_col, "%d:  %-20s  score: %d \t %d min %2d sec ", num, temp->name, temp->score, temp->min, temp->sec);
            else
                mvprintw(i + 4, start_col, "%d: %-20s  score: %d \t %d min %2d sec ", num, temp->name, temp->score, temp->min, temp->sec);

            attroff(A_REVERSE);
            temp = temp->next;
            i++;
            num++; // Incrementa il numero di elemento visualizzato
        }

        ch = getch();
        if (ch == 'Q' || ch == 'q' || ch == 270 || ch == 330) {
            flag=true;; // Esce dal loop e quindi termina il programma
        } else if (ch == KEY_DOWN && num>row-4) {
            // Spostati verso il basso
            if (current->next != NULL) {
                current = current->next;
                offset++;
            }
        } else if (ch == KEY_UP && num>row-4) {
            // Spostati verso l'alto
            if (current != head) {
                PlayerScorePtr prev = head;
                while (prev->next != current) {
                    prev = prev->next;
                }
                current = prev;
                if (offset > 0) {
                    offset--;
                }
            }
        }
    }

    erase();
}