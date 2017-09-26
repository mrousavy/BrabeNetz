#include "stdafx.h"
#include "NeuronFileIO.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int** NeuronFileIO::Read(string path)
{
	ifstream input(path, ios::binary | ios::ate); // Neuron weight inputfile stream
	int length = input.tellg(); // total length of file

	int** weights = new int*[length]; // weights array[][]

	std::vector<char> buffer((
		std::istreambuf_iterator<char>(input)),
		(std::istreambuf_iterator<char>()));

	input.close(); // Close file & release

	return weights;
}

void NeuronFileIO::Write(string path, int** weights)
{
	ofstream output(path, ios::binary); // Neuron weight outputfile stream
	
	// TODO: Iterate over weights and write buffered

	output.close(); // Close file & release
}