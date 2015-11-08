#include "Player.h"

Player* Player::mutate() {
	return new Player();
}

Player* Player::mate(AbstractPlayer*) {
	return new Player();
}
Player* Player::random() {
	return new Player();
}

Player* Player::fromFile(std::string) {
	return new Player();
}
void Player::toFile(std::string) {}

int Player::makeMove(int*, int, int) {
	return 1;
}
