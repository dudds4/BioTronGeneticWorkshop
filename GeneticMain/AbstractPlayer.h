#ifndef ABSTRACTPLAYER_H
#define ABSTRACTPLAYER_H

#include <string>

class AbstractPlayer {
	private:
			int m_id;
	public:
			virtual ~AbstractPlayer(){}
			void setId(int);
			int getId();
			virtual int makeMove(int[][3], int) = 0;
};

#endif
