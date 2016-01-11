#include "Player.h"
#include "globals.cpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

Player::Player():
a(9, 9),
b(9, 9),
c(9, 9),
d(1, 9),
e(9, 9) {
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
	p->a = this->a.add(randomMatrix(9, 9)).scale(0.5);
	p->b = this->b.add(randomMatrix(9, 9)).scale(0.5);
	p->c = this->c.add(randomMatrix(9, 9)).scale(0.5);
	p->d = this->d.add(randomMatrix(1, 9)).scale(0.5);	
	return p;
}

Player* Player::mate(Player* other) {
	Player* p = new Player();
	p->a = this->a.add(other.a).scale(0.5);
	p->b = this->b.add(other.b).scale(0.5);
	p->c = this->c.add(other.c).scale(0.5);
	p->d = this->d.add(other.d).scale(0.5);
	return p;
}
Player* Player::random() {
        Player* p = new Player();
        p->a = randomMatrix(9, 9);
	p->b = randomMatrix(9, 9);
	p->c = randomMatrix(9, 9);
	p->d = randomMatrix(1, 9);
	return p;
}

Player* Player::fromFile(std::string) {
	return new Player();
}
void Player::toFile(std::string) {

}

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
	Matrix s = i1.add(i2).add(i3).add(d);
	
	int maxInd = 0; max = s.get(0, 0);
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
