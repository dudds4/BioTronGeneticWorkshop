#include "Player.h"
#include "globals.cpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <cmath>

Player::Player() {
	time_t timer;
	srand(time(&timer));
}

Player::Player(bool init) {
	time_t timer;
	srand(time(&timer));
	brain = new NeuralNet(18, 9, 2, 50);
}

Player::~Player() {
	delete brain;
}

Player::Player(std::string fileName) {
	time_t timer;
	srand(time(&timer));

	std::ifstream file;
	file.open(fileName);
	
	int input_size, num_layers, layer_size, output_size;
	file >> input_size;
	file >> num_layers;
	file >> layer_size;
	file >> output_size;
	if (input_size != 9 || output_size != 9) {
		file.close();
		return;
	}

	brain = new NeuralNet(input_size, output_size, num_layers, layer_size);

	float connection_weight;
	for (int i=0; i<(input_size+1)*layer_size; i++) {
		file >> connection_weight;
		brain->inputConnections[i] = connection_weight;
	}

	for (int i=0; i<(layer_size+1)*layer_size; i++) {
		for (int j=0; j<input_size; j++) {
			file >> connection_weight;
			brain->midConnections[i][j] = connection_weight;
		}
	}

	for (int i=0; i<(layer_size+1)*output_size; i++) {
		file >> connection_weight;
		brain->outputConnections[i] = connection_weight;
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
	for (int i=0; i<player->brain->layerSize*player->brain->numLayers/8; i++) {
		if (i%3 == 0) {
			random = rand()%((player->brain->inputSize+1)*player->brain->layerSize);
			player->brain->inputConnections[random] += rand()%3-1;
		} else if (i%3 == 1) {
			int n = rand()%player->brain->numLayers-1;
			random = rand()%((player->brain->layerSize+1)*player->brain->layerSize);
			player->brain->midConnections[n][random] += rand()%3-1;
		} else {
			random = rand()%((player->brain->layerSize+1)*player->brain->outputSize);
			player->brain->outputConnections[random] += rand()%3-1;
		}
	}
	return player;
}

Player* Player::mate(Player* parent) {
//	std::cout << "Mate\n";
	Player* child = new Player();
	*(child) = *(this);
	//Fill in this function
	return child;
}
Player* Player::random() {
//	std::cout << "Random\n";
	return new Player(true);
}

int Player::makeMove(int board[][3], int player) {

	float netInput[18] = {0};
	float netOutput[9];

	for (int i=0; i<3; i++) {
		for (int j=0; j<3; j++) {
			if (board[i][j] == player) {
				netInput[3*i+j] = 1;
			} else if (board[i][j] != 0){
				netInput[9+3*i+j] = 1;
			}
		}
	}

	brain->compute(netInput, netOutput);

	int position = 0;
	for (int i=1; i<9; i++) {
		if (netOutput[i] > netOutput[position]) {
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
	file << 9 << std::endl;
	file << brain->numLayers << std::endl;
	file << brain->layerSize << std::endl;
	file << 9 << std::endl;

	for (int i=0; i<(brain->inputSize+1)*brain->layerSize; i++) {
		file << brain->inputConnections[i] << std::endl;	
	}

	for (int i=0; i<brain->numLayers-1; i++) {
		for (int j=0; j<(brain->layerSize+1)*brain->layerSize; j++) {
			file << brain->midConnections[i][j] << std::endl;
		}
	}

	for (int i=0; i<(brain->layerSize+1)*brain->outputSize; i++) {
		file << brain->outputConnections[i] << std::endl;
	}
	file.close();
}