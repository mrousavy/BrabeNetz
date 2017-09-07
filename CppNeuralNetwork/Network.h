#pragma once
class Network
{
public:
	Network(int layerCount);
	~Network();
	void Train(int* inputValues);
};

