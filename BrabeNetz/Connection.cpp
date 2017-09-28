#include "stdafx.h"
#include "Connection.h"


connection::connection()
{
	//this->From = NULL;
	this->to = NULL;
	this->weight = NULL;
}

//Connection::Connection(Neuron* from, Neuron* to, double initialWeight)
//{
//	this->From = from;
//	this->To = to;
//	this->Weight = initialWeight;
//}

connection::~connection()
{}