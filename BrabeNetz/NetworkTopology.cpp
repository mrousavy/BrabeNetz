#include "stdafx.h"
#include "NetworkTopology.h"


NetworkTopology::NetworkTopology()
{
	this->Size = 0;
}

NetworkTopology::~NetworkTopology()
{}

void NetworkTopology::AddLayer(Layer layer)
{
	this->_layers.push_back(layer);
	this->Size++;
}

Layer& NetworkTopology::LayerAt(int index)
{
	return this->_layers.at(index);
}

NetworkTopology NetworkTopology::Random(std::vector<int> layers)
{
	NetworkTopology topology;

	for (int l = 0; l < layers.size(); l++) // Loop through each layer
	{
		Layer layer;

		int lsize = layers.at(l); // Count of neurons in this layer
		for (int n = 0; n < lsize; n++) // Loop through each neuron
		{
			Neuron neuron;
			neuron.Bias = (double(rand() % 200) / 100) - 1; // Random number between 0 and 2, minus 1 (so between -1 and 1)

			int nextNeurons; // Count of neurons in the next layer
			if (l + 1 == layers.size())
				nextNeurons = 0; // Last layer has no connections (no next layer)
			else
				nextNeurons = layers.at(l + 1); // Next layer's neurons

			for (int c = 0; c < nextNeurons; c++) // Loop through each Connection
			{
				Connection connection;
				connection.Weight = (double(rand() % 200) / 100) - 1; // Random number between 0 and 2, minus 1 (so between -1 and 1)
				neuron.AddConnection(connection); // Add Connection from neuron `n`
			}

			layer.AddNeuron(neuron); // Add Neuron from layer `l`
		}

		topology.AddLayer(layer); // Add Layer
	}

	return topology;
}