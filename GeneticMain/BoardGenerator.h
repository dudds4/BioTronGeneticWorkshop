#include <ctime>
#include <algorithm>
#include <cstdlib>


class BoardGenerator {
public:
    BoardGenerator();
    void generateBoard(int[][3], int, bool playerOneFirst=true);
    void generateBoardDef(int[][3]);
    void generateScoreMap(int boardIn[][3], float scoreBoard[][3], int player);
private:
    void genBoard(int[][3], int, bool);
};
