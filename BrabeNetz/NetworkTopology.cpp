#include "stdafx.h"
#include "NetworkTopology.h"

NetworkTopology::NetworkTopology()
{}

NetworkTopology::~NetworkTopology()
{}

void NetworkTopology::AddLayer(Layer layer)
{
	this->Layers.push_back(layer);
}

