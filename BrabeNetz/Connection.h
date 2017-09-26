#pragma once
#include "Neuron.h"

#ifndef Connection_Included
#define Connection_Included

class Neuron;

class Connection
{
public:
	Connection();
	//Connection(Neuron* from, Neuron* to, double initialWeight);
	~Connection();
	/*Neuron* From;
	Neuron* To;*/
	int to;
	double Weight;
};

#endif