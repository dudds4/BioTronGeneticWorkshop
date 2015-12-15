#ifndef PLAYER_H
#define PLAYER_H

#include "AbstractPlayer.h"

class Player : public AbstractPlayer {
	int skill;
public:
	Player();
	Player(int);

	float fitness;
	Player* mutate();
	Player* copy();
	Player* mate(Player*);
	static Player* random();
	
	Player* fromFile(std::string);
	void toFile(std::string);
	
	int makeMove(int[][7], int);
};

/*-------------------SIMPLE ITERATIVE GAME STRATEGY-------------------------*/

int makeMove1(int board[][7], int player);

//Like makeMove1 but randomly chooses one of the best options in case of a tie
int makeMove1random(int board[][7], int player);

//Like makeMove1 but looks 2 moves ahead (assume other player moves randomly)
int makeMove2(int board[][7], int player);

//Like makeMove2 but assumes other player will take best choice give to it
int makeMove2smart(int board[][7], int player);

//Like makeMove2 but looks N moves ahead
int makeMoveN(int board[][7], int player, int n);

//Like makeMove2 but adapts to the percived intelligence of the other player to guess where it will move
int makeMove2adaptive(int board[][7], int player);

/*-----------------(END) SIMPLE ITERATIVE GAME STRATEGY-----------------------*/

#endif
