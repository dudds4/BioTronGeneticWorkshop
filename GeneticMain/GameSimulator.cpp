#include "GameSimulator.h"
#include "Player.h"
#include "DefaultPlayer.h"


GameSimulator::GameSimulator() {
    gameGrid = new int[CELLS];
}

GameSimulator::~GameSimulator() {
    if(gameGrid) {
        delete[] gameGrid;
        gameGrid = NULL;
    }
}

int GameSimulator::exec() {
    DefaultPlayer dp;
    Player p;
    return 0;
}

