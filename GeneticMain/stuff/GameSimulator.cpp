#include "GameSimulator.h"
#include "Player.h"
#include "DefaultPlayer.h"
#include <iostream>

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
    std::cout << "Hello World\n";
    return 0;
}

