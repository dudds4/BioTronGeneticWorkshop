#ifndef PLAYER_H
#define PLAYER_H

#include "AbstractPlayer.h"

class Player : public AbstractPlayer {
public:
	float fitness;
	Player* mutate();
	Player* copy();
	Player* mate(Player*);
	static Player* random();
	
	Player* fromFile(std::string);
	void toFile(std::string);
	
	int makeMove(int[][7], int);
};

#endif
