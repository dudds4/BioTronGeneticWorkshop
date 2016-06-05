#ifndef GLOBALS_CPP
#define GLOBALS_CPP

const int ROWS = 3;
const int COLUMNS = 3;
const int CELLS = 9;

const int DRAW = 0;
const int ERROR = -1;

const int GENERATIONS = 8000;
const int POOL_SIZE = 100;

const int GAMES_PER_MATCH = 20;
const int ILLEGAL_MOVE_THRESHOLD = 10;

const int WIN_WEIGHT = 3; // tinker at will.
const int DRAW_WEIGHT = 1;
const int ILLEGAL_WEIGHT = 5;

#endif
