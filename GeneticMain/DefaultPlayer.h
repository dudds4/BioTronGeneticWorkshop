#ifndef DEFAULTPLAYER_H
#define DEFAULTPLAYER_H

#include "AbstractPlayer.h"

class DefaultPlayer : public AbstractPlayer
{
public:
    DefaultPlayer();
    DefaultPlayer* mutate();
    DefaultPlayer* mate(AbstractPlayer*);
    DefaultPlayer* random();

    DefaultPlayer* fromFile(std::string);
    void toFile(std::string);

    int makeMove(int*, int, int);
};

#endif // DEFAULTPLAYER_H
