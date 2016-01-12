#ifndef PLAYER_H
#define PLAYER_H

#include "AbstractPlayer.h"
#include "Matrix.h"
#include <fstream>

class Player : public AbstractPlayer {
	int skill;
public:
	Player();

	double fitness;
	
	Player* mutate();
	Player* copy();
	Player* mate(Player*);
	static Player* random();
	
	static Player* fromFile(std::string);
	void toFile(std::string);
	
	int makeMove(int[][3], int);
      //----------------------------//
private:
      static Matrix randomMatrix(int, int);
	  void outputMatrixToFile(std::ostream &out, Matrix m); 
	  static void generateMatrixFromFile(std::istream &in, Matrix& m);
      Matrix a;
      Matrix b;
      Matrix c;
      Matrix d;
      Matrix e;
      Matrix f;
      Matrix g;

};

#endif
