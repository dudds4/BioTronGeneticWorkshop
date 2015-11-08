#ifndef ABSTRACTPLAYER_H
#define ABSTRACTPLAYER_H

#include <string>

class AbstractPlayer {
	public:
		virtual AbstractPlayer* mutate() = 0;
		virtual AbstractPlayer* mate(AbstractPlayer*) = 0;
		virtual AbstractPlayer* random() = 0;
		
		virtual AbstractPlayer* fromFile(std::string) = 0;
		virtual void toFile(std::string) = 0;
		
        virtual int makeMove(int*, int, int) = 0;
};

#endif
