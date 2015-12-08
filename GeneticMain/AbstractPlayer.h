#ifndef ABSTRACTPLAYER_H
#define ABSTRACTPLAYER_H

#include <string>

class AbstractPlayer {
	private:
			int m_id;
	public:
			void setId(int);
			int getId();
        	virtual int makeMove(int[][7], int) = 0;
};

#endif
