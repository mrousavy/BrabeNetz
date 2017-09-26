#pragma once
#include <string>

// Helper class for Neuron Weights file on the disk
static class NeuronFileIO
{
public:
	// Read Neuron weights 2D array ([][]) from file
	int** Read(std::string path);
	// Write Neuron weights 2D array ([][]) to file
	void Write(std::string path, int** weights);
};

