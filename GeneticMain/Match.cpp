#include "Match.h"
#include "globals.cpp"

Match::Match() {
}

Match::Match(AbstractPlayer* p1, AbstractPlayer* p2) {
    player1 = p1;
    player2 = p2;
}

Match::~Match() {}

void Match::setPlayer1(AbstractPlayer* p) {
    player1 = p;
    p->setId(0);
}
void Match::setPlayer2(AbstractPlayer* p) {
    player2 = p;
    p->setId(1);
}

void Match::applyMove(int column) {}

int Match::playOut() { //Runs a match and returns the ID of the winner, 0 is a draw
    bool gameOver = false;
    int move = 0, winningPlayer = 0;
    do {
        int column;
        int playerId;
        if (move%2) {
            column = player1->makeMove(matchData, ROWS);
        } else {
            column = player2->makeMove(matchData, ROWS);
        }
        applyMove(column);
        gameOver = checkWinConditions(column);
        move++;
    } while(!gameOver && move < ROWS*COLUMNS);

    if (move == ROWS*COLUMNS)
        return DRAW;
    else {
        if (move%2)
            return player2->getId();
        else
            return player1->getId();
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
