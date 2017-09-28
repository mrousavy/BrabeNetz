#include "stdafx.h"
#include "NetworkTopology.h"


network_topology::network_topology()
{
	this->size = 0;
}

network_topology::~network_topology()
{}

void network_topology::add_layer(layer layer)
{
	this->layers_.push_back(layer);
	this->size++;
}

layer& network_topology::layer_at(int index)
{
	return this->layers_.at(index);
}

network_topology network_topology::random(std::vector<int> layers)
{
	network_topology topology;

	for (int l = 0; l < layers.size(); l++) // Loop through each layer
	{
		layer layer;

		int lsize = layers.at(l); // Count of neurons in this layer
		for (int n = 0; n < lsize; n++) // Loop through each neuron
		{
			neuron neuron;
			neuron.bias = (double(rand() % 200) / 100) - 1; // Random number between 0 and 2, minus 1 (so between -1 and 1)

			int nextNeurons; // Count of neurons in the next layer
			if (l + 1 == layers.size())
				nextNeurons = 0; // Last layer has no connections (no next layer)
			else
				nextNeurons = layers.at(l + 1); // Next layer's neurons

			for (int c = 0; c < nextNeurons; c++) // Loop through each Connection
			{
				connection connection;
				connection.weight = (double(rand() % 200) / 100) - 1; // Random number between 0 and 2, minus 1 (so between -1 and 1)
				neuron.add_connection(connection); // Add Connection from neuron `n`
			}

			layer.add_neuron(neuron); // Add Neuron from layer `l`
		}

		topology.add_layer(layer); // Add Layer
	}

	return topology;
}