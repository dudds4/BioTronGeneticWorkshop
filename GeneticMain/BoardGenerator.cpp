#include <ctime>
#include <cstdlib>
#include "BoardGenerator.h"
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
