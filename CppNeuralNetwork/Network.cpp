#include "stdafx.h"
#include "Network.h"


class Network {
public:
	int* layers;

	// ctor
	Network::Network(int layerCount) {
		layers = new int[layerCount];
	}

	// dctor
	Network::~Network() {
		layers = NULL;
	}

	void Train(int* values) {

	}
};