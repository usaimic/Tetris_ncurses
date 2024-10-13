#include <ctime>
#ifndef SCORE_HPP
#define SCORE_HPP
#define MAX 21

struct PlayerScore {
    char name[MAX]; // Assuming maximum name length of 49 characters
    int score;
    int sec;
    int min;
    PlayerScore* next;
};

typedef PlayerScore* PlayerScorePtr;
void addplayer(char nickname[], int score, int min, int sec);
PlayerScorePtr insertsorted(PlayerScorePtr head, char nickname[], int sc, int minu, int seco);
PlayerScorePtr readFromFile(PlayerScorePtr head);
void displayScores(PlayerScorePtr head);

#endif // SCORE_HPP