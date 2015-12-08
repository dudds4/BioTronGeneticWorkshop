#include "Player.h"

Player* Player::copy() {
	Player* newPlayer = new Player();
	*(newPlayer) = *(this);
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
void Player::toFile(std::string) {}

int Player::makeMove(int[][7], int) {
	return 1;
}
