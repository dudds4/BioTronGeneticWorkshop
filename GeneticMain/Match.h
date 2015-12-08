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
    bool playNextMove();
    Player* getWinningPlayer();
    int getNumMoves();
    int getIllegalMoves(Player* player);
    static const int ROWS = 6;
    static const int COLUMNS = 7;
private:
    int moveNum;
    AbstractPlayer* winningPlayer;
    int illegalMoves[2];
    AbstractPlayer* player1;
    AbstractPlayer* player2;
    int matchData[ROWS][COLUMNS];

    bool checkWinConditions(int);
    bool applyMove(int column, int playerId);
    bool checkForRowWin(int,int);
    bool checkForColumnWin(int,int);
    bool checkForDiagonalWin(int,int);
};

#endif // MATCH_H
