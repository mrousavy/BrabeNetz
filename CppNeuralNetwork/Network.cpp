//#ifndef Network_Header
//#define Network_Header

#include "stdafx.h"
#include "Network.h"


	int* layers;

	// ctor
	Network::Network(int layerCount) {
		layers = new int[layerCount];
	}

	// dctor
	Network::~Network() {
		layers = NULL;
	}

	void Network::Train(int* values) {

	}

//#endif