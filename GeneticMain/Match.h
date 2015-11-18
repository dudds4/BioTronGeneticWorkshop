#ifndef MATCH_H
#define MATCH_H

#include "AbstractPlayer.h"

class Match
{
public:
    Match();
    Match(AbstractPlayer*, AbstractPlayer*);
    ~Match();
    void setPlayer1(AbstractPlayer*);
    void setPlayer2(AbstractPlayer*);
    int playOut();
    bool checkWinConditions(int);

private:
    AbstractPlayer* player1;
    AbstractPlayer* player2;
    int matchData[ROWS][COLUMNS];

    bool checkForRowWin(int,int);
    bool checkForColumnWin(int,int);
    bool checkForDiagonalWin(int,int)

};

#endif // MATCH_H
