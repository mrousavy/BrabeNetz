#pragma once
#include <string>

// Helper class for Neuron Weights file on the disk
static class neuron_file_io
{
public:
	// Read Neuron weights 2D array ([][]) from file
	static int** read(std::string path);
	// Write Neuron weights 2D array ([][]) to file
	static void write(std::string path, int** weights);
};

