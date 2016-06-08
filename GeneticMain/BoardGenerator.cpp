#include <ctime>
#include <cstdlib>
#include "BoardGenerator.h"
#include "globals.cpp"

bool simulateBoard(int (**board)[3], int position, int playerId);
void clearSimulation(int (**board)[3], int position);
int getConsecutiveHorizontal(int board[][3], int i, int j);
int getConsecutiveVertical(int board[][3], int i, int j);
int getConsecutivePositiveDiagonal(int board[][3], int i, int j);
int getConsecutiveNegativeDiagonal(int board[][3], int i, int j);
int getScore(int board[][3], int player);

BoardGenerator::BoardGenerator(){
    srand(time(0));
}

void BoardGenerator::generateBoard(int boardOut[][3], int numMoves, bool playerOneFirst){
    genBoard(boardOut, numMoves, playerOneFirst);
}

void BoardGenerator::generateBoardDef(int boardOut[][3]){
    int numMoves = rand() % 10;
    genBoard(boardOut, numMoves, true);
}

void BoardGenerator::genBoard(int boardOut[][3], int numMoves, bool playerOneFirst){
    //set the board to all 0's at first
    for(int i = 0; i < 9; i++)
        boardOut[i/3][i%3] = 0;

    if(numMoves <= 0 || numMoves >= 9) return;
    
    //figure out which IDs to use
    int firstID = playerOneFirst ? 1 : 2;
    int secondID = (firstID % 2) + 1;

    //start filling the board (deterministic, random)
    int turn = 0;
    while(turn < numMoves) {
        //spotToPlayOn is the nth empty spot
        //if there are 8 empty spots left we only need a random number from 1-8
        int spotToPlayOn = (rand() % (9-turn))+1;
        int indexToPlayOn = -1;
        for(int i = 0; i < spotToPlayOn; i++) {
            while(boardOut[(indexToPlayOn+1)/3][(indexToPlayOn+1)%3] != 0) {
                indexToPlayOn++;
            }
            indexToPlayOn++;
        }
        
        boardOut[indexToPlayOn/3][indexToPlayOn%3] = (turn % 2) ? secondID : firstID;
        turn++;
    }
}

void BoardGenerator::generateScoreMap(int boardIn[][3], float scoreBoard[][3], int player) {
    float score, sum=0;
    // Calculate desirability of each location on the board
    for (int i=0; i<9; i++) {
        if (simulateBoard(&boardIn, i, player)) {
            score = getScore(boardIn, player);
            scoreBoard[i/3][i%3] = score;
            sum += score;
            clearSimulation(&boardIn, i);
        } else {
            scoreBoard[i/3][i%3] = -1000;
        }
    }

    //Normalize the board such that the sum of viable entries is 1
    for (int i=0; i<9; i++) {
        scoreBoard[i/3][i%3] /= sum;
    }
}

bool simulateBoard(int (**board)[3], int position, int playerId) {
    if ((*board)[position/3][position%3] == 0) {
        (*board)[position/3][position%3] = playerId;
        return true;
    }
    else return false;
}

void clearSimulation(int (**board)[3], int position) {
    //Todo: error checking
    (*board)[position/3][position%3] = 0;
}

int getConsecutiveHorizontal(int board[][3], int i, int j) {
    //Count horizontal and return it. If you run into a tile that's already been read, return 0 since this row has already been counted
    int consecutive = 1;
    int playerNum = board[i][j];

    int c = j;
    while ((--c) >= 0) {
        if (board[i][c] == playerNum)
            consecutive++;
        else if (board[i][c] == -playerNum)
            return 0;
        else
            break;
    }

    c = j;
    while ((++c) < COLUMNS) {
        if (board[i][c] == playerNum)
            consecutive++;
        else if (board[i][c] == -playerNum)
            return 0;
        else
            break;
    }
    return consecutive;
}

int getConsecutiveVertical(int board[][3], int i, int j) {
    int consecutive = 1;
    int playerNum = board[i][j];

    int r = i;
    while ((--r) >= 0) {
        if (board[r][j] == playerNum)
            board++;
        else if (board[r][j] == -playerNum)
            return 0;
        else
            break;
    }

    r = i;
    while ((++r) < ROWS) {
        if (board[r][j] == playerNum)
            consecutive++;
        else if (board[r][j] == -playerNum)
            return 0;
        else
            break;
    }
    return consecutive;
}

int getConsecutivePositiveDiagonal(int board[][3], int i, int j) {
    int consecutive = 1;
    int playerNum = board[i][j];

    int r = i;
    int c = j;

    while ( (++r) < ROWS && (--c) >= 0 ) {
        if (board[r][c] == playerNum)
            consecutive++;
        else if (board[r][c] == -playerNum)
            return 0;
        else
            break;
    }

    r = i;
    c = j;
    while ( (--r) >= 0 && (++c) < COLUMNS ) {
        if (board[r][c] == playerNum)
            consecutive++;
        else if (board[r][c] == -playerNum)
            return 0;
        else
            break;
    }

    return consecutive;
}

int getConsecutiveNegativeDiagonal(int board[][3], int i, int j) {
    int consecutive = 1;
    int playerNum = board[i][j];

    int r = i;
    int c = j;
    while ( (--r) >= 0 && (--c) >= 0 ) {
        if (board[r][c] == playerNum)
            consecutive++;
        else if (board[r][c] == -playerNum)
            return 0;
        else
            break;
    }

    r = i;
    c = j;
    while ( (++r) < ROWS && (++c) < COLUMNS) {
        if (board[r][c] == playerNum)
            consecutive++;
        else if (board[r][c] == -playerNum)
            return 0;
        else
            break;
    }

    return consecutive;
}

//Option 1: Getting 3 in a row (1000 points)
//Option 2: Blocking a 3 in a row (200 points)
//Option 3: Getting two 2 in a row
//2 in a row -> 600 points
//Opponent 3 in a row -> -700 points
//Opponent 2 in a row -> -200 points
int getScore(int board[][3], int player) {
    int score = 0, consecutive;
    int boardCopy[3][3];
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            boardCopy[i][j] = board[i][j];
        }
    }
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            if (boardCopy[i][j] == player) {
                consecutive = getConsecutiveHorizontal(boardCopy, i, j);
                if (consecutive == 3) score += 1000;
                if (consecutive == 2) score += 60;
                consecutive = getConsecutiveVertical(boardCopy, i, j);
                if (consecutive == 3) score += 100;
                if (consecutive == 2) score += 60;
                consecutive = getConsecutivePositiveDiagonal(boardCopy, i, j);
                if (consecutive == 3) score += 100;
                if (consecutive == 2) score += 60;
                consecutive = getConsecutiveNegativeDiagonal(boardCopy, i, j);
                if (consecutive == 3) score += 1000;
                if (consecutive == 2) score += 60;
            } else if (boardCopy[i][j] != 0) {
                consecutive = getConsecutiveHorizontal(boardCopy, i, j);
                if (consecutive == 3) score -= 300;
                if (consecutive == 2) score -= 70;
                consecutive = getConsecutiveVertical(boardCopy, i, j);
                if (consecutive == 3) score -= 300;
                if (consecutive == 2) score -= 70;
                consecutive = getConsecutivePositiveDiagonal(boardCopy, i, j);
                if (consecutive == 3) score -= 300;
                if (consecutive == 2) score -= 70;
                consecutive = getConsecutiveNegativeDiagonal(boardCopy, i, j);
                if (consecutive == 3) score -= 300;
                if (consecutive == 2) score -= 70;
            }
            boardCopy[i][j] *= -1; //Marks that it has already been counted (no effect on empty tile cuz duh)
        }
    }
    return score+300; //300 bias to keep score positive
}