#ifndef PLAYER_H
#define PLAYER_H

#include "AbstractPlayer.h"
#include "Matrix.h"
#include <fstream>

class Player : public AbstractPlayer {
	int skill;
	/*
	Place Data Structure Here
	*/
public:
	Player();

	double fitness;
	
	Player* mutate();
	Player* copy();
	Player* mate(Player*);
	static Player* random();
	
	static Player* fromFile(std::string);
	void toFile(std::string);
	
	void makeMove(int[][3], int, double[]);
      //----------------------------//
private:
      static Matrix randomMatrix(int, int);
	  void outputMatrixToFile(std::ostream &out, Matrix m); 
	  static void generateMatrixFromFile(std::istream &in, Matrix& m);
      double quickSigmoid(double);
      Matrix applySigmoid(Matrix m);
      Matrix theta1;
      Matrix theta2;
      Matrix theta3;
};

#endif
