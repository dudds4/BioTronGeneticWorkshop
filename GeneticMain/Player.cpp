#include "Player.h"
#include "globals.cpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

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

int Player::makeMove(int board[][3], int player) {
	return rand()%9;
}