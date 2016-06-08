#include <iostream>
#include "BoardGenerator.h"

using namespace std;

int main() {
	BoardGenerator boardGen;
    int boardInput[3][3];
    float scoreMap[3][3];
    double output[9];
	for (int n=0; n<20; n++) {
        int numMoves = n%9;
        //Generate Random Board
        boardGen.generateBoard(boardInput, numMoves);
        //Generate Expected Output Score Map
        boardGen.generateScoreMap(boardInput, scoreMap, (numMoves%2) + 1);

        for (int i=0; i<3; i++) {
        	for (int j=0; j<3; j++) {
        		cout << boardInput[i][j] << " (" << scoreMap[i][j] << ")\t\t";
        	} cout << endl;
        } cout << endl;
 	}
}