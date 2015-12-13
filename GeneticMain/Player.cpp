#include "Player.h"

#include <cstdlib>
#include <ctime>

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

int Player::makeMove(int[][7], int) {
	return (rand()%7);

	//return 1;
}
