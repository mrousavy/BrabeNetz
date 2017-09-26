#include "stdafx.h"
#include "NetworkTopology.h"

NetworkTopology::NetworkTopology()
{
	this->Layers = new std::vector<Layer*>();
}

NetworkTopology::~NetworkTopology()
{
	delete this->Layers;
}

void NetworkTopology::AddLayer(Layer* layer)
{
	this->Layers->push_back(layer);
}

