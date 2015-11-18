#include "Match.h"
#include "globals.cpp"

Match::Match() {
}

Match::Match(AbstractPlayer* p1, AbstractPlayer* p2) {
    player1 = p1;
    player2 = p2;
}

Match::~Match() {
    if(matchData) {
        delete[] matchData;
        matchData = NULL;
    }
}

void Match::setPlayer1(AbstractPlayer* p) {
    player1 = p;
}
void Match::setPlayer2(AbstractPlayer* p) {
    player2 = p;
}

int Match::playOut() { //Runs a match and returns the ID of the winner, 0 is a draw
    bool gameOver = false;
    int move = 0, winningPlayer = 0;
    do {
        if (move%2) {
            column = player1.makeMove(matchData);
        } else {
            column = player2.makeMove(matchData);
        }
        applyMove(column);
        gameOver = checkWinConditions(column);
        move++;
    } while(!gameOver && move < ROWS*COLUMNS);

    if (move == ROWS*COLUMNS)
        return DRAW;
    else {
        if (move%2)
            return player2.getId();
        else
            return player1.getId();
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
        return true
    }
    
    return false;
}

bool Match::checkForRowWin(int row, int column) {
    if(cell >= CELLS || cell < 0) return false;

    int consecutive = 1;
    int playerNum = matchData[cell];

    int firstIndexInRow = (cell / COLUMNS) * COLUMNS;
    int lastIndexInRow = (cell / COLUMNS + 1) * COLUMNS - 1;

    int i = cell - 1;
    while(i >= firstIndexInRow && matchData[i] == playerNum) {
        consecutive += 1;
        i--;
    }
    i = cell + 1;
    while(i <= lastIndexInRow && matchData[i] == playerNum) {
        consecutive += 1;
        i++;
    }
    return consecutive > 3;
}

bool Match::checkForColumnWin(int row, int column) {
    if(cell >= CELLS || cell < 0) return false;

    int consecutive = 1;
    int playerNum = matchData[cell];

    int firstIndexInCol = (cell / COLUMNS) * COLUMNS;
    int lastIndexInCol = (cell / COLUMNS + 1) * COLUMNS - 1;
    return false;
}
