#ifndef MATCH_H
#define MATCH_H

#include "AbstractPlayer.h"

class Match
{
public:
    static const int ROWS = 6;
    static const int COLUMNS = 7;
	
    Match();
    Match(AbstractPlayer*, AbstractPlayer*);
    ~Match();
    void setPlayer1(AbstractPlayer*);
    void setPlayer2(AbstractPlayer*);
    int playOut();
    bool playNextMove();
	bool copyBoardOut(int[][COLUMNS], int);
	
    AbstractPlayer* getWinningPlayer();
    int getNumMoves();
    int getIllegalMoves(AbstractPlayer* player);

private:
    int moveNum;
    bool m_gameOver = false;
    AbstractPlayer* winningPlayer;
    int illegalMoves[2];
    AbstractPlayer* player1;
    AbstractPlayer* player2;
    int matchData[ROWS][COLUMNS];

    void printBoard();
    int checkWinConditions(int);
    bool applyMove(int column, int playerId);
    bool checkForVerticalWin(int,int);
    bool checkForHorizontalWin(int,int);
    bool checkForDiagonalWin(int,int);
};

#endif // MATCH_H
