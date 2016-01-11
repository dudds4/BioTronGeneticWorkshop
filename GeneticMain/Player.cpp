#include "Player.h"
#include "globals.cpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

Player::Player() {
	time_t timer;
	srand(time(&timer));
//  Instantiates a new Player
}

Player* Player::copy() {
	Player* newPlayer = new Player();
	*(newPlayer) = *(this);
	return newPlayer;
}

Player* Player::mutate() {
//  Returns a copy of current player
//  with minor random differences.
	return new Player();
}

Player* Player::mate(Player* p2) {
//  Returns a new player whose data
//	structure mixes the data from p2 and
//  the current player
	return new Player();
}
Player* Player::random() {
//	Returns a player with entirely randomized data
	return new Player();
}

Player* Player::fromFile(std::string fileName) {
//  Returns a player whose data structure is outlined in a file
	return new Player();
}
void Player::toFile(std::string fileName) {
//  Stores the player's data into a file
}

int Player::makeMove(int board[][3], int player) {
//  Given a board and the current player's ID,
//  returns a position where the Player would like to play.
	return rand()%9;
}