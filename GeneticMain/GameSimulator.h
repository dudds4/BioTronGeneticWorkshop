#ifndef GAMESIMULATOR_H
#define GAMESIMULATOR_H

#include "geneticmain_global.h"
#include "globals.cpp"

class GameSimulator
{

public:
    GameSimulator();
    ~GameSimulator();
    int exec();
private:
    int* gameGrid;
};

#endif // GAMESIMULATOR_H
