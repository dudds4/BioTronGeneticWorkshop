#include "Player.h"
#include "globals.cpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>

Player::Neuron::Neuron() {
	in = 42;
	out = 7;
	inputWeights = new int[in];
	outputWeights = new int[out];
	for (int i = 0; i < in; i++) {
		inputWeights[i] = rand()%50;
	}
	for (int i = 0; i < out; i++) {
		outputWeights[i] = rand()%50;
	}
}

Player::Neuron::Neuron(int _in, int _out) {
	in = _in;
	out = _out;
	inputWeights = new int[in];
	outputWeights = new int[out];
	for (int i = 0; i < in; i++) {
		inputWeights[i] = rand()%50;
	}
	for (int i = 0; i < out; i++) {
		outputWeights[i] = rand()%50;
	}
}

void Player::Neuron::mutate() {
	for (int i = 0; i < in; i++) {
		inputWeights[i] += 3-(int)pow(rand()%216,1/3);
		if (inputWeights[i] < 0) {
			inputWeights[i] = 0;
		} else if (inputWeights[i] > 50) {
			inputWeights[i] = 50;
		}
	}
	for (int i = 0; i < out; i++) {
		outputWeights[i] += 3-(int)pow(rand()%216,1/3);
		if (outputWeights[i] < 0) {
			outputWeights[i] = 0;
		} else if (outputWeights[i] > 50) {
			outputWeights[i] = 50;
		}
	}
}

Player::Brain::Brain() {
	size = neuronCount;
}

Player::Brain::Brain(int _size) {
	size = _size;
}

void Player::Brain::init(int _in, int _out, int _size) {
	in = _in;
	out = _out;
	size = _size;
	neurons = new Neuron[size];
	for (int i=0; i<size; i++) {
		neurons[i] = Neuron(in, out);
	}
}

void Player::Brain::execute(int input[], int inputSize, int output[], int outputSize) {
	if (outputSize != neurons[0].out || inputSize != neurons[0].in) {
		std::cout << "Wrong size, quitting\n";
		return;
	}// std::cout << "Executing\n";
	for (int i=0; i<outputSize; i++) {
		output[i] = 0;
	}
	for (int i=0; i<size; i++) {
		neurons[i].value = 0;
		for (int j=0; j<inputSize; j++) {
			neurons[i].value += 10*input[j]*neurons[i].inputWeights[j]+neurons[i].inputWeights[j];
		}
		for (int j=0; j<outputSize; j++) {
			output[j] += neurons[i].outputWeights[j]*neurons[i].value;
		}
	}
}

Player::Player() {
	time_t timer;
	srand(time(&timer));
}

Player::Player(bool init) {
	if (init) {
		brain1.init(42,20,30);
		brain2.init(42,20,30);
		brain3.init(20,7,40);
	}
}

Player* Player::copy() {
//	std::cout << "Copy\n";
	Player* newPlayer = new Player();
	*(newPlayer) = *(this);
	return newPlayer;
}

Player* Player::mutate() {
//	std::cout << "Mutate\n";
	int random;
	Player* player = new Player();
	*player = *this;
	for (int i=0; i<brain1.size/2; i++) {
		random = rand()%brain1.size;
		if (i%2 == 0) {
			player->brain1.neurons[random].mutate();
		} else {
			player->brain2.neurons[random].mutate();
		}
	}
	for (int i=0; i<brain3.size/4; i++) {
		random = rand()%brain3.size;
		player->brain3.neurons[random].mutate();
	}
	return player;
}

Player* Player::mate(Player* parent) {
//	std::cout << "Mate\n";
	Player* child = new Player();
	*(child) = *(this);
	for (int i=0; i<brain1.size; i++) {
		if (rand()%2 == 0) {
			child->brain1.neurons[i] = parent->brain1.neurons[i];
		}
		if (rand()%2 == 0) {
			child->brain2.neurons[i] = parent->brain2.neurons[i];
		}
	}
	for (int i=0; i<brain3.size; i++) {
		if (rand()%2 == 0) {
			child->brain3.neurons[i] = parent->brain3.neurons[i];
		}
	}
	return child;
}
Player* Player::random() {
//	std::cout << "Random\n";
	return new Player(true);
}

Player* Player::fromFile(std::string) {
	return new Player();
}
void Player::toFile(std::string) {

}

int Player::makeMove(int board[][7], int player) {
	int columns[7];
	int midSize = 20;

	//Brain1
	int p1Board[42], p1Output[midSize];
	for (int i=0; i<6; i++) {
		for (int j=0; j<7; j++) {
			if (board[i][j] == player) {
				p1Board[7*i+j]=1;
			} else {
				p1Board[7*i+j]=0;
			}
		}
	}
	brain1.execute(p1Board, 42, p1Output, midSize);

	//Brain2
	int p2Board[42], p2Output[midSize];
	for (int i=0; i<6; i++) {
		for (int j=0; j<7; j++) {
			if (board[i][j] != player && board[i][j] != 0) {
				p2Board[7*i+j]=1;
			} else {
				p2Board[7*i+j]=0;
			}
		}
	}
	brain2.execute(p2Board, 42, p2Output, midSize);

	int p3Board[midSize], p3Output[7];
	for (int i=0; i<midSize; i++) {
		p3Board[i] = p1Output[i] + p2Output[i];
	}
	brain3.execute(p3Board, midSize, columns, 7);

	int column = 0;
	for (int i=1; i<7; i++) {
		if (columns[i] > columns[column]) {
			column = i;
		}
	}
	return column;
}