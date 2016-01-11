#ifndef PLAYER_H
#define PLAYER_H

#include "AbstractPlayer.h"

class Player : public AbstractPlayer {
	int skill;
	/*
	Place Data Structure Here
	*/
public:
	Player();

	double fitness;
	
	Player* mutate();
	Player* copy();
	Player* mate(Player*);
	static Player* random();
	
	static Player* fromFile(std::string);
	void toFile(std::string);
	
	int makeMove(int[][3], int);
};

#endif
