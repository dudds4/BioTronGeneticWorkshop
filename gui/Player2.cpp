#include "Player2.h"
#include "../GeneticMain/globals.cpp"

#include <cstdlib>
#include <ctime>
#include <iostream>

#define Player Player2

Player::Player() {
	time_t timer;
	srand(time(&timer));
}

Player* Player::copy() {
	Player* newPlayer = new Player();
	*(newPlayer) = *(this);
	return newPlayer;
}

Player* Player::mutate() {
	return new Player();
}

Player* Player::mate(Player*) {
	return new Player();
}
Player* Player::random() {
	return new Player();
}

Player* Player::fromFile(std::string) {
	return new Player();
}
void Player::toFile(std::string) {

}

int Player::makeMove(int board[][7], int player) {
	return rand()%7;
}

#undef Player
