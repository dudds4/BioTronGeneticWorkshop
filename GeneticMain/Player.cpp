#include "Player.h"
#include "globals.cpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

Player::Player():
a(9, 18),
b(9, 18),
c(9, 18),
d(18, 9),
e(18, 9),
f(18, 9),
g(1, 9) {
	time_t timer;
	srand(time(&timer));
//  Instantiates a new Player
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
	p->a = this->a.add(randomMatrix(9, 18)).scale(0.5);
	p->b = this->b.add(randomMatrix(9, 18)).scale(0.5);
	p->c = this->c.add(randomMatrix(9, 18)).scale(0.5);
	p->d = this->d.add(randomMatrix(18, 9)).scale(0.5);	
	p->e = this->e.add(randomMatrix(18, 9)).scale(0.5);
	p->f = this->f.add(randomMatrix(18, 9)).scale(0.5);	
	p->g = this->g.add(randomMatrix(1, 9)).scale(0.5);
	return p;
}

//  Returns a new player whose data
//	structure mixes the data from p2 and
//  the current player
Player* Player::mate(Player* other) {
	Player* p = new Player();
	p->a = this->a.add(other->a).scale(0.5);
	p->b = this->b.add(other->b).scale(0.5);
	p->c = this->c.add(other->c).scale(0.5);
	p->d = this->d.add(other->d).scale(0.5);
	p->e = this->e.add(other->e).scale(0.5);
	p->f = this->f.add(other->f).scale(0.5);
	p->g = this->g.add(other->g).scale(0.5);
	
	return p;
}

//	Returns a player with entirely randomized data
Player* Player::random() {
        Player* p = new Player();
        p->a = randomMatrix(9, 18);
	p->b = randomMatrix(9, 18);
	p->c = randomMatrix(9, 18);
	p->d = randomMatrix(18, 9);
	p->e = randomMatrix(18, 9);
	p->f = randomMatrix(18, 9);
	p->g = randomMatrix(1, 9);

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
	generateMatrixFromFile(fin, p->a);
	generateMatrixFromFile(fin, p->b);
	generateMatrixFromFile(fin, p->c);
	generateMatrixFromFile(fin, p->d);
	generateMatrixFromFile(fin, p->e);
	generateMatrixFromFile(fin, p->f);
	generateMatrixFromFile(fin, p->g);	
	
	return p;
}
//  Stores the player's data into a file
void Player::toFile(std::string fileName) {
	std::ofstream fout;
	fout.open(fileName.c_str());
	
	outputMatrixToFile(fout, this->a);
	outputMatrixToFile(fout, this->b);
	outputMatrixToFile(fout, this->c);
	outputMatrixToFile(fout, this->d);
	outputMatrixToFile(fout, this->e);
	outputMatrixToFile(fout, this->f);
	outputMatrixToFile(fout, this->g);	
}

//  Given a board and the current player's ID,
//  returns a position where the Player would like to play.
int Player::makeMove(int board[][3], int player) {
        Matrix mySpaces(1, 9);
        Matrix enemySpaces(1, 9);
        Matrix nonEmpty(1, 9);
	int row, col;        
	for(int i = 0; i < 9; i++) {
		row = i / 3;
		col = i % 3;
        }
	Matrix i1 = mySpaces.rightMultiply(a);
	Matrix i2 = enemySpaces.rightMultiply(b);
	Matrix i3 = nonEmpty.rightMultiply(c);

	Matrix s1 = i1.add(i2).rightMultiply(d);
	Matrix s2 = i1.add(i3).rightMultiply(e);
	Matrix s3 = i2.add(i3).rightMultiply(f);

	Matrix s = s1.add(s2).add(s3).add(g);
	
	int maxInd = 0, max = s.get(0, 0);
	for(int i = 1; i < 9; i++) {
		if(s.get(0, i) > max) {
			max = s.get(0, i);
			maxInd = i;
		}
	}

	return maxInd;
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
