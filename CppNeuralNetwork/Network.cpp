#include "stdafx.h"
#include "Network.h"


int* layers;

// ctor
Network::Network(int layerCount)
{
	if (layerCount < 1) throw "Layer count cannot be 0 or less!";
	layers = new int[layerCount];
}

// dctor
Network::~Network()
{
	layers = NULL;
}

void Network::Train(int* inputValues, int* weights, int expectedOutput)
{

}