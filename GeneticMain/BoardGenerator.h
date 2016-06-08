#include <ctime>
#include <algorithm>
#include <cstdlib>


class BoardGenerator {
public:
    BoardGenerator();
    void generateBoard(int[][3], int, bool);
    void generateBoardDef(int[][3]);
private:
    void genBoard(int[][3], int, bool);
};
