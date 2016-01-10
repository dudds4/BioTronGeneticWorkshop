#include "Player.h"
#include "globals.cpp"
#include <cstdlib>
#include <ctime>
#include <fstream>

Player::Player():
a(7, 6),
b(7, 6),
c(7, 6),
d(7, 7), 
e(1, 7),
f(7, 1) {
	time_t timer;
	srand(time(&timer));
}

Player* Player::copy() {
	Player* newPlayer = new Player();
	*(newPlayer) = *(this);
	return newPlayer;
}

Player* Player::mutate() {
	Player* p = new Player();
	p->a = this->a.add(randomMatrix(7, 6)).scale(0.5);
	p->b = this->b.add(randomMatrix(7, 6)).scale(0.5);
	p->c = this->c.add(randomMatrix(7, 6)).scale(0.5);
	p->d = this->d.add(randomMatrix(7, 7)).scale(0.5);
	p->e = this->e.add(randomMatrix(1, 7)).scale(0.5);
	p->f = this->f.add(randomMatrix(7, 1)).scale(0.5);

	return p;
}

Player* Player::mate(Player* other) {
	Player* p = new Player();

	p->a = this->a.add(other->a).scale(0.5);
	p->b = this->b.add(other->b).scale(0.5);
	p->c = this->c.add(other->c).scale(0.5);	
	p->d = this->d.add(other->d).scale(0.5);
	p->e = this->e.add(other->e).scale(0.5);
	p->f = this->f.add(other->f).scale(0.5);

	return p;
}
Player* Player::random() {
	Player* p = new Player();
	p->a = randomMatrix(7, 6);
	p->b = randomMatrix(7, 6);
	p->c = randomMatrix(7, 6);
	p->d = randomMatrix(7, 7);
	p->e = randomMatrix(1, 7);
	p->e = randomMatrix(7, 1);
	
	return p;
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

Player* Player::fromFile(std::string fileName) {
	std::ifstream fin;
	fin.open(fileName.c_str());
	Player* p = new Player();
	Matrix aIn(7, 6);
	Matrix bIn(7, 6);
	Matrix cIn(7, 6);
	Matrix dIn(7, 7);
	Matrix eIn(1, 7);
	Matrix fIn(7, 1);

	generateMatrixFromFile(fin, aIn);
	generateMatrixFromFile(fin, bIn);
	generateMatrixFromFile(fin, cIn);
	generateMatrixFromFile(fin, dIn);
	generateMatrixFromFile(fin, eIn);
	generateMatrixFromFile(fin, fIn);

	p->a = aIn;
	p->b = bIn;
	p->c = cIn;
	p->d = dIn;
	p->e = eIn;
	p->f = fIn;

	return new Player();
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

void Player::toFile(std::string fileName) {
	std::ofstream fout;
	fout.open(fileName.c_str());

	outputMatrixToFile(fout, this->a);
	outputMatrixToFile(fout, this->b);
	outputMatrixToFile(fout, this->c);
	outputMatrixToFile(fout, this->d);
	outputMatrixToFile(fout, this->e);
	outputMatrixToFile(fout, this->f);
}

int Player::makeMove(int board[][7], int player) {
	Matrix spacesIOwn(6, 7);
	Matrix spacesOpponentOwns(6, 7);
	Matrix nonEmptySpaces(6, 7);

	for(int r = 0; r < 6; r++)
		for(int c = 0; c < 7; c++) {
			spacesIOwn.set(r, c, (board[r][c] == player));
			spacesOpponentOwns.set(r, c, (board[r][c] != player && board[r][c] != 0));
			nonEmptySpaces.set(r, c, (board[r][c] != 0));
		}

	Matrix result_a_mine = a.rightMultiply(spacesIOwn);
	Matrix result_b_opponents = b.rightMultiply(spacesOpponentOwns);
	Matrix result_c_nonEmpty = c.rightMultiply(nonEmptySpaces);

	Matrix sum = result_a_mine
					.add(result_b_opponents)
					.add(result_c_nonEmpty)
					.add(d);



	Matrix final = e.rightMultiply(sum).rightMultiply(f);
	int columnToPlayOn = final.get(0, 0) % 7;
	return columnToPlayOn;

	// int max = final.get(0, 0);
	// int indexOfMax = 0;
	// for(int i = 1; i < 7; i++) {
	// 	int value = final.get(0, i);
	// 	if(value > max) {
	// 		max = value;
	// 		indexOfMax = i;
	// 	}
	// }

	// return indexOfMax;
}

Matrix Player::randomMatrix(int rows, int cols) {
	Matrix r(rows, cols);
	for(int i = 0; i < rows; i++)
		for(int j = 0; j < cols; j++)
			r.set(i, j, rand()%1000);

	return r;
}