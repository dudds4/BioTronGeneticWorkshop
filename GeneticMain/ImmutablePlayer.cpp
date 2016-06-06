#include "ImmutablePlayer.h"
#include "globals.cpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

ImmutablePlayer::ImmutablePlayer() {
	time_t timer;
	srand(time(&timer));
	skill = 0;
}

ImmutablePlayer::ImmutablePlayer(int _skill) {
	time_t timer;
	srand(time(&timer));
	skill = _skill;
}

void ImmutablePlayer::makeMove(int board[][7], int player, double output[]) {
    int chosen;

    switch (skill) {
        case 0:
            chosen=rand()%7;
        case 1:
            chosen=makeMove1(board, player);
        case 2:
            chosen=makeMove1random(board, player);
        case 3:
            chosen=makeMove2(board, player);
        case 4:
            chosen=makeMove2smart(board, player);
        case 5:
            chosen=makeMove2adaptive(board, player);
        default:
            chosen=makeMoveN(board, player, skill-3); //skill level 6 looks 3 moves ahead, level 7 looks 4, and level 8 looks 5
	}

    for(int i = 0; i < 9; i++)
        output[i] = (i == chosen) ? 1 : 0;

    return; 
}


/*---------------------SIMPLE ITERATIVE GAME STRATEGY-----------------------*/

bool ImmutablePlayer::simulateBoard(int (**board)[7], int column, int playerId) {
	for (int i = ROWS - 1; i >= 0; i--) {
		if ((*board)[i][column] == 0) {
			(*board)[i][column] = playerId;
			break;
		} else if (i == 0) {
			return false;
		}
	} return true;
}

void ImmutablePlayer::clearSimulation(int (**board)[7], int column) {
	//Todo: error checking
	for (int i = 0; i < ROWS; i++) {
		if ((*board)[i][column] != 0) {
			(*board)[i][column] = 0;
			break;
		}
	}
}

int ImmutablePlayer::getConsecutiveHorizontal(int board[][7], int i, int j) {
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

int ImmutablePlayer::getConsecutiveVertical(int board[][7], int i, int j) {
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

int ImmutablePlayer::getConsecutivePositiveDiagonal(int board[][7], int i, int j) {
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

int ImmutablePlayer::getConsecutiveNegativeDiagonal(int board[][7], int i, int j) {
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

//4 in a row -> 10000 points
//3 in a row -> 600 points
//2 in a row -> 150 points
//Opponent 3 in a row -> -700 points
//Opponent 2 in a row -> -200 points
int ImmutablePlayer::getScore(int board[][7], int player) {
	int score = 0, consecutive;
	int boardCopy[6][7];
	for (int i=0; i<6; i++) {
		for (int j=0; j<7; j++) {
			boardCopy[i][j] = board[i][j];
		}
	}
	for (int i=0; i<6; i++) {
		for (int j=0; j<7; j++) {
			if (boardCopy[i][j] == player) {
				consecutive = getConsecutiveHorizontal(boardCopy, i, j);
				if (consecutive == 4) score += 100000;
				if (consecutive == 3) score += 600;
				if (consecutive == 2) score += 150;
				consecutive = getConsecutiveVertical(boardCopy, i, j);
				if (consecutive == 4) score += 10000;
				if (consecutive == 3) score += 600;
				if (consecutive == 2) score += 150;
				consecutive = getConsecutivePositiveDiagonal(boardCopy, i, j);
				if (consecutive == 4) score += 10000;
				if (consecutive == 3) score += 600;
				if (consecutive == 2) score += 150;
				consecutive = getConsecutiveNegativeDiagonal(boardCopy, i, j);
				if (consecutive == 4) score += 100000;
				if (consecutive == 3) score += 600;
				if (consecutive == 2) score += 150;
			} else if (boardCopy[i][j] != 0) {
				consecutive = getConsecutiveHorizontal(boardCopy, i, j);
				if (consecutive == 4) score -= 20000;
				if (consecutive == 3) score -= 700;
				if (consecutive == 2) score -= 200;
				consecutive = getConsecutiveVertical(boardCopy, i, j);
				if (consecutive == 4) score -= 20000;
				if (consecutive == 3) score -= 700;
				if (consecutive == 2) score -= 200;
				consecutive = getConsecutivePositiveDiagonal(boardCopy, i, j);
				if (consecutive == 4) score -= 20000;
				if (consecutive == 3) score -= 700;
				if (consecutive == 2) score -= 200;
				consecutive = getConsecutiveNegativeDiagonal(boardCopy, i, j);
				if (consecutive == 4) score -= 20000;
				if (consecutive == 3) score -= 700;
				if (consecutive == 2) score -= 200;
			}
			boardCopy[i][j] *= -1; //Marks that it has already been counted (no effect on empty tile cuz duh)
		}
	}
	return score;
}

int ImmutablePlayer::makeMove1(int board[][7], int player) {
	int tempScore, column, bestScore = 0;

	for (int i=0; i<7; i++) {
		if (simulateBoard(&board, i, player)) {
			tempScore = getScore(board, player);
			std::cout << i << ": " << tempScore << "  ";
			if (tempScore > bestScore || i == 0) {
				column = i;
				bestScore = tempScore;
			}
			clearSimulation(&board, i);
		}
	}
	std::cout << std::endl;
	return column;
}

int ImmutablePlayer::makeMove1random(int board[][7], int player) {
	int tempScore, column, bestScore = 0;
	int possibleMoves[7];

	for (int i=0; i<7; i++) {
		if (simulateBoard(&board, i, player)) {
			tempScore = getScore(board, player);
			std::cout << i << ": " << tempScore << "  ";
			if (tempScore > bestScore || i == 0) {
				column = i;
				bestScore = tempScore;
				for (int j=0; j<7; j++) {
					possibleMoves[j] = 0;
				}
				possibleMoves[i] = 1;
			} else if (tempScore == bestScore) {
				possibleMoves[i] = 1;
			}
			clearSimulation(&board, i);
		}
	}
	int numPossibleMoves = 0;
	for (int i=0; i<7; i++) {
		if (possibleMoves[i] == 1) {
			numPossibleMoves++;
		}
	}
	int counter = 0;
	int move = rand()%numPossibleMoves;
	for (int i=0; i<7; i++) {
		if (possibleMoves[i] == 1) {
			if (counter == move) {
				return i;
			}
			counter++;
		}
	}
	std::cout << std::endl;
	return column; //just in case
}

//Like makeMove1 but looks 2 moves ahead (assume other player moves randomly)
int ImmutablePlayer::makeMove2(int board[][7], int player) {
	int tempScore, column, bestScore = 0;
	//todo this
	int enemy_player = (player == 1) ? 2 : 1;

	for (int i=0; i<7; i++) {
		if (simulateBoard(&board, i, player)) {
			tempScore = 0;
			for (int j=0; j<7; j++) {
				if (simulateBoard(&board, j, enemy_player)) {
					tempScore += getScore(board, player);
					clearSimulation(&board, j);
				}
			}
			std::cout << i << ": " << tempScore << "  ";
			if (tempScore > bestScore || i == 0) {
				column = i;
				bestScore = tempScore;
			}
			clearSimulation(&board, i);
		}
	}
	std::cout << std::endl;
	return column;
}

//Like makeMove2 but assumes other player will take best choice give to it
int ImmutablePlayer::makeMove2smart(int board[][7], int player) {
	int tempScore, column, bestScore = 0;
	//todo this
	int enemy_player = (player == 1) ? 2 : 1;
	int enemy_move;

	for (int i=0; i<7; i++) {
		if (simulateBoard(&board, i, player)) {
			enemy_move = makeMove1(board, enemy_player);
			if (simulateBoard(&board, enemy_move, enemy_player)) {
				tempScore = getScore(board, player);
				std::cout << i << ": " << tempScore << "  ";
				if (tempScore > bestScore || i == 0) {
					column = i;
					bestScore = tempScore;
				}
				clearSimulation(&board, enemy_move);
			}
			clearSimulation(&board, i);
		}
	}
	std::cout << std::endl;
	return column;
}

//Like makeMove2 but looks N moves ahead
int ImmutablePlayer::makeMoveN(int board[][7], int player, int n) {
	int MAX_MOVES = 5;
	//todo: Actually implement this and do it recursively
	if (n < 1 || n > MAX_MOVES) {
		return rand()%7;
	} else if (n == 1) {
		return makeMove1(board, player);
	} else {
		return makeMove2(board, player);
	}
}

//Like makeMove2 but adapts to the percived intelligence of the other player to guess where it will move
int ImmutablePlayer::makeMove2adaptive(int board[][7], int player) {
	//Would have to store the last_board after it makes a move and then compare it to the next board it
	//recieves to see what it's opponent did. Then evaluate how smart of a move that was to determine
	//how to guess how it will play next.
	return rand()%7;
}

/*-----------------(END) SIMPLE ITERATIVE GAME STRATEGY-----------------------*/
