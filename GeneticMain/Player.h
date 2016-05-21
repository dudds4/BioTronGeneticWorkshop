#ifndef PLAYER_H
#define PLAYER_H

#include "AbstractPlayer.h"

class Player : public AbstractPlayer {
	class Neuron {
	public:
		Neuron();
		Neuron(int, int);
		void mutate();
		int value;
		int numInputs, numOutputs;
		int* outputWeights;
		int* inputWeights;
	};
	class Brain {
	public:
		Brain();
		int in, out, size;
		void init(int, int, int);
		void execute(int in[], int, int out[], int);
		Neuron *neurons;
	};
	Brain brain1, brain2, brain3;
public:
	double fitness;
	Player();
	Player(bool init);
	Player(std::string);
	
	Player* mutate();
	Player* copy();
	Player* mate(Player*);
	static Player* random();
	
	static Player* fromFile(std::string);
	void toFile(std::string);
	
	int makeMove(int[][3], int);
};

#endif
