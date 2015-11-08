#include "Match.h"
#include "globals.cpp"

Match::Match() {
    matchData = new int[CELLS];
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

int Match::playOut() {}
int Match::checkWinConditions() {
    for(int i = 0; i < CELLS; i++) {


    }
}

bool Match::checkForRowWin(int cell) {
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

bool Match::checkForColumnWin(int cell) {
    if(cell >= CELLS || cell < 0) return false;

    int consecutive = 1;
    int playerNum = matchData[cell];

    int firstIndexInCol = (cell / COLUMNS) * COLUMNS;
    int lastIndexInCol = (cell / COLUMNS + 1) * COLUMNS - 1;
}
