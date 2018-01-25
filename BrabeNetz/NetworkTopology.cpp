#include "NetworkTopology.h"
#include <fstream>


network_topology::network_topology()
{
}

network_topology::~network_topology()
{
}

std::ostream& operator<<(std::ostream& os, network_topology& nt)
{
	int size = nt.size();
	os.write(reinterpret_cast<const char*>(&size), sizeof(size));
	for (int i = 0; i < size; i++)
		os << nt.layer_at(i);
	return os;
}

std::istream& operator>>(std::istream& is, network_topology& nt)
{
	int size;
	is.read(reinterpret_cast<char*>(&size), sizeof(size));
	nt.layers_.reserve(size);
	for (int i = 0; i < size; i++)
		nt.layers_.push_back(network_topology::read_layer(is));
	return is;
}

layer network_topology::read_layer(std::istream& is)
{
	layer l;
	is >> l;
	return l;
}

void network_topology::add_layer(layer& layer)
{
	this->layers_.push_back(layer);
}

layer& network_topology::layer_at(const int index)
{
	return this->layers_.at(index);
}

network_topology& network_topology::random(std::vector<int> layers)
{
	auto* topology = new network_topology(); // Alloc on heap

	for (int l = 0; l < layers.size(); l++) // Loop through each layer
	{
		layer layer;

		const int lsize = layers.at(l); // Count of neurons in this layer
		for (int n = 0; n < lsize; n++) // Loop through each neuron
		{
			neuron neuron;
			if (l != 0) // Layer0 (input) does not have any bias
				neuron.bias = (double(rand() % 200) / 100) - 1; // Random number between 0 and 2, minus 1 (so between -1 and 1)

			int next_neurons; // Count of neurons in the next layer
			if (l + 1 == layers.size())
				next_neurons = 0; // Last layer has no connections (no next layer)
			else
				next_neurons = layers.at(l + 1); // Next layer's neurons

			for (int c = 0; c < next_neurons; c++) // Loop through each Connection
			{
				// Random number between 0 and 2, minus 1 (so between -1 and 1)
				connection connection(double(rand() % 200) / 100 - 1);
				neuron.add_connection(connection); // Add Connection from neuron `n`
			}

			layer.add_neuron(neuron); // Add Neuron from layer `l`
		}

		topology->add_layer(layer); // Add Layer
	}

	return *topology;
}

network_topology& network_topology::load(const std::string path)
{
	network_topology* topology = new network_topology();

	std::ifstream file;
	file.open(path, std::fstream::in | std::fstream::binary); // Open the file
	file >> *topology; // Deserialize network topology with operator>>
	file.close();

	return *topology;
}

void network_topology::save(network_topology& topology, const std::string path)
{
	std::ofstream file;
	file.open(path, std::fstream::out | std::fstream::binary | std::fstream::trunc); // Open the file
	file << topology; // Serialize network topology with operator<<
	file.close();
}

int network_topology::clear(const std::string path)
{
	return remove(path.c_str());
}
