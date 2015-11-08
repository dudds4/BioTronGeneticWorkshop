#ifndef PLAYER_H
#define PLAYER_H

#include "AbstractPlayer.h"

class Player : AbstractPlayer {
	public:
		Player* mutate();
		Player* mate(AbstractPlayer*);
		Player* random();
		
		Player* fromFile(std::string);
		void toFile(std::string);
		
        int makeMove(int*, int, int);
};

#endif
