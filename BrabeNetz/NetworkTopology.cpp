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
