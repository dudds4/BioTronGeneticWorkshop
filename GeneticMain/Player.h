#ifndef PLAYER_H
#define PLAYER_H

#include "AbstractPlayer.h"
#include "NeuralNet.h"

class Player : public AbstractPlayer {
	NeuralNet* brain;
public:
	double fitness;
	Player();
	Player(bool init);
	Player(std::string);
	~Player();
	
	Player* mutate();
	Player* copy();
	Player* mate(Player*);
	static Player* random();
	
	static Player* fromFile(std::string);
	void toFile(std::string);
	
	int makeMove(int[][3], int);
};

#endif
