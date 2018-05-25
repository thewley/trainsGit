//	Jonathan Bengtsson
//	Projekt Trains V1.0
//	Headerfil för fordon

#ifndef FORDON_H
#define FORDON_H

#include<iostream>

class Fordon
{
protected:
	int fordonID;

public:
	Fordon(int aFordonID) : fordonID(aFordonID) {};
	virtual ~Fordon() { std::cout << "~Fordon" << std::endl; }
	virtual void print() = 0;
};

#endif