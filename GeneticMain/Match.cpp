#include "Match.h"
#include "globals.cpp"
#include <cstdlib>
#include <ctime>

Match::Match() {
    srand(time(0));
    moveNum = 0;
    illegalMoves[0] = 0;
    illegalMoves[1] = 0;
    winningPlayer = NULL;
}

Match::Match(AbstractPlayer* p1, AbstractPlayer* p2) {
    srand(time(0));
    moveNum = 0;
    player1 = p1;
    player2 = p2;
    player1->setId(1);
    player2->setId(2);
    illegalMoves[0] = 0;
    illegalMoves[1] = 0;
    winningPlayer = NULL;
}

Match::~Match() {}

void Match::setPlayer1(AbstractPlayer* p) {
    player1 = p;
    player1->setId(1);
}
void Match::setPlayer2(AbstractPlayer* p) {
    player2 = p;
    player2->setId(2);
}

bool Match::applyMove(int column, int playerId) {
    for (int i=ROWS-1; i>=0; i++) {
        if (matchData[i][column] == 0) {
            matchData[i][column] = playerId;
        } else if (i == 0) {
            return false;
        }
    }
    return true;
}

bool Match::playNextMove() {
    int column;
    AbstractPlayer* p = moveNum%2 ? player1 : player2;
    column = p->makeMove(matchData, ROWS);

    if (!applyMove(column, (moveNum%2)+1)) {
        illegalMoves[moveNum%2]++;
        if (illegalMoves[moveNum%2] > ILLEGAL_MOVE_THRESHOLD) {
            winningPlayer = moveNum%2 ? player2 : player1;
            return true;
        }
        do {
            column = rand()%COLUMNS;
        } while (!applyMove(column, (moveNum%2)+1));
    }
    if (checkWinConditions(column)) {
        winningPlayer = p;
        return true;
    }
    moveNum++;
    return false;
}

int Match::playOut() { //Runs a match and returns the int of the winning player, 0 is a draw
    bool gameOver = false;
    do {
        gameOver = playNextMove();
    } while(!gameOver && moveNum < ROWS*COLUMNS);

    if (!gameOver) {
        return DRAW;
    } else {
        return (winningPlayer == player1) ? 1 : 2;
    }
}

bool Match::checkWinConditions(int column) {
    int row = 6;
    while(row >= 0) {
        if (matchData[row][column] != 0) break;
        row--;
    } if (row == -1) {
        return ERROR;
    }

    if (
        checkForRowWin(row,column) ||
        checkForColumnWin(row,column) ||
        checkForDiagonalWin(row,column)
    ) {
        return true;
    }
    
    return false;
}

bool Match::checkForRowWin(int row, int column) {
    //TODO: false isn't an appropriate return value
    if(row < 0 || row >= ROWS) return false;
    if(column < 0 || column >= COLUMNS) return false;

    int consecutive = 1;
    int playerNum = matchData[row][column];

    int r = row;
    while((--r) >= 0 && matchData[r][column] == playerNum)
        consecutive+=1;

    r = row;
    while((++r) < COLUMNS && matchData[r][column] == playerNum)
        consecutive+=1;

    return consecutive > 3;
}

bool Match::checkForColumnWin(int row, int column) {
    //TODO: false isn't an appropriate return value
    if(row < 0 || row >= ROWS) return false;
    if(column < 0 || column >= COLUMNS) return false;

    int consecutive = 1;
    int playerNum = matchData[row][column];

    int c = column;
    while((--c) >= 0 && matchData[row][c] == playerNum)
        consecutive++;

    c = column;
    while((++c) < COLUMNS && matchData[row][c] == playerNum)
        consecutive++;

    return consecutive > 3;
}

bool Match::checkForDiagonalWin(int row, int column) {
    //TODO: false isn't an appropriate return value
    if(row < 0 || row >= ROWS) return false;
    if(column < 0 || column >= COLUMNS) return false;

    int consecutive = 1;
    int playerNum = matchData[row][column];

    //negative slope diagonal check
    int r = row;
    int c = column;
    while(  (--r) >= 0 && 
            (--c) >= 0 && 
            matchData[r][c] == playerNum) 
        consecutive++;

    while(  (++r) < ROWS    && 
            (++c) < COLUMNS && 
            matchData[r][c] == playerNum) 
        consecutive++;

    if(consecutive > 3) return true;
    
    consecutive = 1;
    r = row;
    c = column;

    while(  (++r) < ROWS &&
            (--c) >= 0 && 
            matchData[r][c] == playerNum) 
        consecutive++;

    while(  (--r) >= 0    &&
            (++c) < COLUMNS && 
            matchData[r][c] == playerNum) 
        consecutive++;

    return consecutive > 3;
}

Player* Match::getWinningPlayer() {
    return winningPlayer;
}
int Match::getNumMoves() {
    return moveNum;
}
int Match::getIllegalMoves(Player* player) {
    if (player == player1) {
        return illegalMoves[0];
    } else {
        return illegalMoves[1];
    }
}