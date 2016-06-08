#include "NeuralNet.h"
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>

NeuralNet::NeuralNet() {
	srand(time(0));
	inputSize = 0;
	outputSize = 0;
	numLayers = 0;
	layerSize = 0;
}

NeuralNet::NeuralNet(int input, int output, int layers, int size) {
	//Initialize parameters as 2D float array with proper dimensions (accounting for bias terms)
	//Populate parameters randomly
	srand(time(0));
	inputSize = input;
	outputSize = output;
	numLayers = layers;
	layerSize = size;

	inputConnections = new float [(inputSize+1)*layerSize];
	if (numLayers > 1) {
		midConnections = new float* [numLayers - 1];
		for (int i=0; i<numLayers-1; i++) {
			midConnections[i] = new float [(layerSize+1)*layerSize];
		}
	}
	outputConnections = new float [(layerSize+1)*outputSize];

	neurons = new float* [numLayers];
	for (int i=0; i<numLayers; i++) {
		neurons[i] = new float [layerSize];
	}

	randomize();
}

NeuralNet::~NeuralNet() {
	delete[] inputConnections;
	delete[] outputConnections;
	
	for (int i=0; i<numLayers-1; i++) {
		delete[] midConnections[i];
	}
	delete[] midConnections;

	for (int i=0; i<numLayers; i++) {
		delete[] neurons[i];
	}
	delete[] neurons;
}

void NeuralNet::randomize() {
	for (int i=0; i<(inputSize+1)*layerSize; i++) {
		inputConnections[i] = rand()%2000/100.0-10;
	}

	for (int i=0; i<numLayers-1; i++) {
		for (int j=0; j<(layerSize+1)*layerSize; j++) {
			midConnections[i][j] = rand()%2000/100.0-10;
		}
	}

	for (int i=0; i<(layerSize+1)*outputSize; i++) {
		outputConnections[i] = rand()%2000/100.0-10;
	}
}

void NeuralNet::compute(float input[], float output[]) {

	if (numLayers < 1) return;			//No support for 0 layers

	float sum;
	for (int i=0; i<layerSize; i++) {
		sum = inputConnections[(inputSize+1)*i];		//bias term
		for (int j=0; j<inputSize; j++) {
			sum += input[j]*inputConnections[(inputSize+1)*i+j+1];
		}
		neurons[0][i] = sigmoid(sum);
	}

	for (int n=1; n<numLayers; n++) {
		for (int i=0; i<layerSize; i++) {
			sum = midConnections[n-1][(layerSize+1)*i];	//bias term
			for (int j=0; j<layerSize; j++) {
				sum += neurons[n-1][j]*midConnections[n-1][(layerSize+1)*i+j+1];
			}
			neurons[n][i] = sigmoid(sum);
		}
	}

	for (int i=0; i<outputSize; i++) {
		sum = outputConnections[(layerSize+1)*i];		//bias term
		for (int j=0; j<layerSize; j++) {
			sum += neurons[numLayers-1][j]*outputConnections[(layerSize+1)*i+j+1];
		}
		output[i] = sigmoid(sum);
	}
}

float NeuralNet::sigmoid(float t) {
	return ((t / (1 + fabs(t))) + 1)/2;
}