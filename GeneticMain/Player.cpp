#include "Player.h"
#include "globals.cpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <cmath>

Player::Neuron::Neuron() {
	numInputs = 42;
	numOutputs = 7;
	inputWeights = new int[numInputs];
	outputWeights = new int[numOutputs];
	for (int i = 0; i < numInputs; i++) {
		inputWeights[i] = rand()%50;
	}
	for (int i = 0; i < numOutputs; i++) {
		outputWeights[i] = rand()%50;
	}
}

Player::Neuron::Neuron(int _inputs, int _outputs) {
	numInputs = _inputs;
	numOutputs = _outputs;
	inputWeights = new int[numInputs];
	outputWeights = new int[numOutputs];
	for (int i = 0; i < numInputs; i++) {
		inputWeights[i] = rand()%50;
	}
	for (int i = 0; i < numOutputs; i++) {
		outputWeights[i] = rand()%50;
	}
}

void Player::Neuron::mutate() {
	for (int i = 0; i < numInputs; i++) {
		inputWeights[i] += (2*(rand()%2)-1)*(10-(int)pow(rand()%100,1/2));
		if (inputWeights[i] < 0) {
			inputWeights[i] = 0;
		} else if (inputWeights[i] > 50) {
			inputWeights[i] = 50;
		}
	}
	for (int i = 0; i < numOutputs; i++) {
		outputWeights[i] += (2*(rand()%2)-1)*(10-(int)pow(rand()%100,1/2));
		if (outputWeights[i] < 0) {
			outputWeights[i] = 0;
		} else if (outputWeights[i] > 50) {
			outputWeights[i] = 50;
		}
	}
}

Player::Brain::Brain() { }

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
	if (outputSize != neurons[0].numOutputs || inputSize != neurons[0].numInputs) {
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
	time_t timer;
	srand(time(&timer));
	if (init) {
		brain1.init(9,15,100);
		brain2.init(9,15,100);
		brain3.init(15,9,80);
	}
}

Player::Player(std::string fileName) {
	time_t timer;
	srand(time(&timer));

	std::ifstream file;
	file.open(fileName);

	brain1.init(9,15,100);
	brain2.init(9,15,100);
	brain3.init(15,9,80);
	
	int input_size, b1, b2, mid_size, b3, output_size;
	file >> input_size;
	file >> b1;
	file >> b1;
	file >> mid_size;
	file >> b3;
	file >> output_size;
	if (input_size != 9 || output_size != 9) {
		file.close();
		return;
	}

	int input_weight, output_weight;
	for (int i=0; i<brain1.size; i++) {
		for (int j=0; j<input_size; j++) {
			file >> input_weight;
			brain1.neurons[i].inputWeights[j] = input_weight;
		}
		for (int j=0; j<mid_size; j++) {
			file >> output_weight;
			brain1.neurons[i].outputWeights[j] = output_weight;
		}
	}

	for (int i=0; i<brain2.size; i++) {
		for (int j=0; j<input_size; j++) {
			file >> input_weight;
			brain2.neurons[i].inputWeights[j] = input_weight;
		}
		for (int j=0; j<mid_size; j++) {
			file >> output_weight;
			brain2.neurons[i].outputWeights[j] = output_weight;
		}
	}

	for (int i=0; i<brain3.size; i++) {
		for (int j=0; j<mid_size; j++) {
			file >> input_weight;
			brain3.neurons[i].inputWeights[j] = input_weight;
		}
		for (int j=0; j<output_size; j++) {
			file >> output_weight;
			brain3.neurons[i].outputWeights[j] = output_weight;
		}
	}
	file.close();
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
	for (int i=0; i<brain1.size/8; i++) {
		random = rand()%brain1.size;
		if (i%2 == 0) {
			player->brain1.neurons[random].mutate();
		} else {
			player->brain2.neurons[random].mutate();
		}
	}
	for (int i=0; i<brain3.size/16; i++) {
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

int Player::makeMove(int board[][3], int player) {
	int positions[9];
	int midSize = 15;

	//Brain1
	int p1Board[9], p1Output[midSize];
	for (int i=0; i<3; i++) {
		for (int j=0; j<3; j++) {
			if (board[i][j] == player) {
				p1Board[3*i+j]=1;
			} else {
				p1Board[3*i+j]=0;
			}
		}
	}
	brain1.execute(p1Board, 9, p1Output, midSize);

	//Brain2
	int p2Board[9], p2Output[midSize];
	for (int i=0; i<3; i++) {
		for (int j=0; j<3; j++) {
			if (board[i][j] != player && board[i][j] != 0) {
				p2Board[3*i+j]=1;
			} else {
				p2Board[3*i+j]=0;
			}
		}
	}
	brain2.execute(p2Board, 9, p2Output, midSize);

	int p3Board[midSize];
	for (int i=0; i<midSize; i++) {
		p3Board[i] = p1Output[i] + p2Output[i];
	}
	brain3.execute(p3Board, midSize, positions, 9);

	int position = 0;
	for (int i=1; i<9; i++) {
		if (positions[i] > positions[position]) {
			position = i;
		}
	}
	return position;
}

Player* Player::fromFile(std::string fileName) {
	return new Player(fileName);
}

void Player::toFile(std::string fileName) {
	std::ofstream file;
	file.open(fileName);
	int midSize = 15;
	file << 9 << std::endl;
	file << brain1.size << std::endl;
	file << brain2.size << std::endl;
	file << midSize << std::endl;
	file << brain3.size << std::endl;
	file << 9 << std::endl;

	for (int i=0; i<brain1.size; i++) {
		for (int j=0; j<9; j++) {
			file << brain1.neurons[i].inputWeights[j] << std::endl;
		}
		for (int j=0; j<midSize; j++) {
			file << brain1.neurons[i].outputWeights[j] << std::endl;
		}
	}

	for (int i=0; i<brain2.size; i++) {
		for (int j=0; j<9; j++) {
			file << brain2.neurons[i].inputWeights[j] << std::endl;
		}
		for (int j=0; j<midSize; j++) {
			file << brain2.neurons[i].outputWeights[j] << std::endl;
		}
	}

	for (int i=0; i<brain3.size; i++) {
		for (int j=0; j<midSize; j++) {
			file << brain3.neurons[i].inputWeights[j] << std::endl;
		}
		for (int j=0; j<9; j++) {
			file << brain3.neurons[i].outputWeights[j] << std::endl;
		}
	}
	file.close();
}