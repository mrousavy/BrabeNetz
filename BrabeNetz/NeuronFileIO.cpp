#include "stdafx.h"
#include "NeuronFileIO.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int** neuron_file_io::read(const string path)
{
	ifstream input(path, ios::binary | ios::ate); // Neuron weight inputfile stream
	const int length = input.tellg(); // total length of file

	int** weights = new int*[length]; // weights array[][]

	std::vector<char> buffer((
		std::istreambuf_iterator<char>(input)),
		(std::istreambuf_iterator<char>()));

	input.close(); // Close file & release

	return weights;
}

void neuron_file_io::write(const string path, int** weights)
{
	ofstream output(path, ios::binary); // Neuron weight outputfile stream
	
	// TODO: Iterate over weights and write buffered

	output.close(); // Close file & release
}
