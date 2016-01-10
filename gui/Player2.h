#ifndef PLAYER_H2
#define PLAYER_H2

#include "../GeneticMain/AbstractPlayer.h"
#define Player Player2

class Player : public AbstractPlayer {
	int skill;
public:
	Player();

	double fitness;
	
	Player* mutate();
	Player* copy();
	Player* mate(Player*);
	static Player* random();
	
	static Player* fromFile(std::string);
	void toFile(std::string);
	
	int makeMove(int[][7], int);
};

#undef Player
#endif
