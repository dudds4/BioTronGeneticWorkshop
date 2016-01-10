#ifndef PLAYER_H
#define PLAYER_H

#include "AbstractPlayer.h"

#define neuronCount 200

class Player : public AbstractPlayer {
	int skill;
	class Neuron {
	public:
		Neuron();
		Neuron(int, int);
		void mutate();
		int value;
		int in, out;
		int* outputWeights;
		int* inputWeights;
	};
	class Brain {
	public:
		Brain();
		Brain(int _size);
		int in, out, size;
		void init(int, int, int);
		void execute(int in[], int, int out[], int);
		Neuron *neurons;
	};
	Brain brain1, brain2, brain3;
public:
	Player();
	Player(bool init);

	double fitness;
	
	Player* mutate();
	Player* copy();
	Player* mate(Player*);
	static Player* random();
	
	static Player* fromFile(std::string);
	void toFile(std::string);
	
	int makeMove(int[][7], int);
};

#endif
