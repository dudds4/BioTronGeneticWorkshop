#ifndef MATCH_H
#define MATCH_H

#include "AbstractPlayer.h"

class Match
{
public:
    Match();
    ~Match();
    void setPlayer1(AbstractPlayer*);
    void setPlayer2(AbstractPlayer*);
    int playOut();
    int checkWinConditions();

private:
    AbstractPlayer* player1;
    AbstractPlayer* player2;
    int* matchData;

    bool checkForRowWin(int);
    bool checkForColumnWin(int);

};

#endif // MATCH_H
