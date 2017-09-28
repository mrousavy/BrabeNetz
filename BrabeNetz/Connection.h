#pragma once
#include "Neuron.h"

#ifndef CONNECTION_INCLUDED
#define CONNECTION_INCLUDED

class neuron;

class connection
{
public:
	connection();
	//Connection(Neuron* from, Neuron* to, double initialWeight);
	~connection();
	/*Neuron* From;
	Neuron* To;*/
	int to;
	double weight;
};

#endif