#include "Player.h"
#include "globals.cpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

#define fabs(T) ((T)>0 ? (T) : -1*(T))

Player::Player():
theta1(19, 18),
theta2(19, 9) {
	time_t timer;
	srand(time(&timer));
//  Instantiates a new Player
}

Matrix Player::getTheta1() {
    return theta1;
}

Matrix Player::getTheta2() {
    return theta2;
}

bool Player::setTheta1(Matrix m) {
    if(m.numRows() != 19 || m.numCols() != 18) return false;
    theta1 = m;
    return true;
}
bool Player::setTheta2(Matrix m) {
    if(m.numRows() != 19 || m.numCols() != 9) return false;
    theta2 = m;
    return true;
}
bool Player::setTheta1(int row, int col, double val) {
    if(row < 0 || row >= theta1.numRows()) return false;
    if(col < 0 || col >= theta1.numCols()) return false;
    theta1.set(row, col, val);
    return true;
}
bool Player::setTheta2(int row, int col, double val) {
    if(row < 0 || row >= theta2.numRows()) return false;
    if(col < 0 || col >= theta2.numCols()) return false;
    theta2.set(row, col, val);
    return true;
}

Player* Player::copy() {
	Player* newPlayer = new Player();
	*(newPlayer) = *(this);
	return newPlayer;
}

//  Returns a copy of current player
//  with minor random differences.
Player* Player::mutate() {
	Player* p = new Player();
	p->theta1 = this->theta1.add(randomMatrix(19, 18)).scale(0.5);
	p->theta2 = this->theta2.add(randomMatrix(19, 9)).scale(0.5);
	return p;
}

//  Returns a new player whose data
//	structure mixes the data from p2 and
//  the current player
Player* Player::mate(Player* other) {
	Player* p = new Player();
	p->theta1 = this->theta1.add(other->theta1).scale(0.5);
	p->theta2 = this->theta2.add(other->theta2).scale(0.5);
	
	return p;
}

//	Returns a player with entirely randomized data
Player* Player::random() {
    Player* p = new Player();
    p->theta1 = randomMatrix(19, 18);
    p->theta2 = randomMatrix(19, 9);

	return p;
}

void Player::outputMatrixToFile(std::ostream &out, Matrix m) {
    int rows = m.numRows();
    int cols = m.numCols();

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            out << m.get(i, j) << " ";
        }
        out << std::endl;
    }
    out << std::endl;
}

void Player::generateMatrixFromFile(std::istream &in, Matrix& m) {
    int rows = m.numRows();
    int cols = m.numCols();
    int value;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j< cols; j++) {
            in >> value;
            m.set(i, j, value);
        }
    }
}

//  Returns a player whose data structure is outlined in a file
Player* Player::fromFile(std::string fileName) {
	std::ifstream fin;
	fin.open(fileName.c_str());
	
	Player* p = new Player();
	generateMatrixFromFile(fin, p->theta1);
	generateMatrixFromFile(fin, p->theta2);
	
	return p;
}
//  Stores the player's data into a file
void Player::toFile(std::string fileName) {
	std::ofstream fout;
	fout.open(fileName.c_str());
	
	outputMatrixToFile(fout, this->theta1);
	outputMatrixToFile(fout, this->theta2);
}

double Player::quickSigmoid(double x) {
    return ((x / (1.0 + fabs(x))) + 1.0)/2.0;
}

Matrix Player::applySigmoid(Matrix m) {
    for(int i = 0; i < m.numRows(); i++)
        for(int j = 0; j < m.numCols(); j++) {
            double a = m.get(i, j);
            m.set(i, j, quickSigmoid(a));
        }

    return m;
}

//  Given a board and the current player's ID,
//  returns a position where the Player would like to play.
void Player::makeMove(int board[][3], int player, double output[]) {

    //feature extraction
    Matrix inputVector(1, 19);
	int row, col;
    inputVector.set(0, 0, 1);        
	for(int i = 0; i < 9; i++) {
        row = i/3;
        col = i%3;
	    inputVector.set(0, i, (board[row][col] == player));
	    inputVector.set(0, i+9, (board[row][col] && board[row][col] != player));
    }

    //neural net forward propagation
    Matrix secondLayer = applySigmoid(inputVector.rightMultiply(theta1));
	for(int i = 0; i < 18; i++) {
	    inputVector.set(0, i+1, secondLayer.get(0, i));
    }

    Matrix outputLayer = applySigmoid(inputVector.rightMultiply(theta2));

    //copy result into output "vector"
    for(int i = 0; i < 9; i++)
        output[i] = outputLayer.get(0, i); 
    return; 	
}

Matrix Player::randomMatrix(int width, int height) {
    Matrix result(width, height);
    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
            result.set(i, j, (rand()%20)*(rand()%2 ? -1 : 1));
        }
    }
    return result;
}
