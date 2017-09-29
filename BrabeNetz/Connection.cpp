#include "stdafx.h"
#include "Connection.h"


connection::connection()
{
	//this->From = NULL;
	this->to = NULL;
	this->weight = NULL;
}

connection::~connection()
{
}

std::ostream& operator<<(std::ostream& os, const connection& c)
{
	os.write(reinterpret_cast<const char*>(&c.weight), sizeof c.weight);
	return os;
}

std::istream& operator>>(std::istream& is, connection& c)
{
	is.read(reinterpret_cast<char*>(&c.weight), sizeof c.weight);
	return is;
}
