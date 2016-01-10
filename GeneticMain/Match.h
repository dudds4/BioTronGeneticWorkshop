#ifndef MATCH_H
#define MATCH_H

#include "AbstractPlayer.h"
#include "globals.cpp"

class Match
{
public:
    Match();
    Match(AbstractPlayer*, AbstractPlayer*);
    ~Match();
    void setPlayer1(AbstractPlayer*);
    void setPlayer2(AbstractPlayer*);
    int playOut();
    int playOutVerbose();
    bool playNextMove();
	bool copyBoardOut(int[][COLUMNS], int);
	
    AbstractPlayer* getWinningPlayer();
    int getNumMoves();
    int getIllegalMoves(AbstractPlayer* player);

private:
    int moveNum;
    bool m_gameOver;
    AbstractPlayer* winningPlayer;
    int illegalMoves[2];
    AbstractPlayer* player1;
    AbstractPlayer* player2;
    int matchData[ROWS][COLUMNS];
    int m_test;

    void printBoard();
    int checkWinConditions(int, int);
    bool applyMove(int row, int column, int playerId);
    bool checkForVerticalWin(int,int);
    bool checkForHorizontalWin(int,int);
    bool checkForDiagonalWin(int,int);
};

#endif // MATCH_H
