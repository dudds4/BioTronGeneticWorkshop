#ifndef PLAYER_H
#define PLAYER_H

#include "AbstractPlayer.h"
#include "Matrix.h"


class Player : public AbstractPlayer {
	int skill;
public:
	Player();

	double fitness;
	
	Player* mutate();
	Player* copy();
	Player* mate(Player*);
	
	static Player* random();
	static void generateMatrixFromFile(std::istream &in, Matrix& m); 
	static Player* fromFile(std::string);
	static void outputMatrixToFile(std::ostream &out, Matrix m);

	void toFile(std::string);
	
	int makeMove(int[][7], int);

	//----------------------------------------

	static Matrix randomMatrix(int, int);

	Matrix a;
	Matrix b;
	Matrix c;
	Matrix d;
	Matrix e;
	Matrix f;

};

#endif
