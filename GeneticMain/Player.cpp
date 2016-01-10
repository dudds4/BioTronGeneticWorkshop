#include "Player.h"
#include "globals.cpp"
#include <cstdlib>
#include <ctime>

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

Player* Player::fromFile(std::string fileName) {
	return new Player();
}
void Player::toFile(std::string fileName) {

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