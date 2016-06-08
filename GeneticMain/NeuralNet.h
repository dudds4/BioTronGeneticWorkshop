#ifndef NEURALNET_H
#define NEURALNET_H

class NeuralNet {
private:
	float **neurons;
	float sigmoid(float t);	//Sigmoid activation function - approximated to improve speed
public:
	NeuralNet();
	NeuralNet(int input, int output, int layers, int size);
	~NeuralNet();
	void compute(float input[], float output[]);
	void randomize();
	int inputSize, outputSize, numLayers, layerSize;
	float *inputConnections, **midConnections, *outputConnections;
};

#endif