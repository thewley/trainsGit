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
	int fordonType;

public:
	Fordon(int aFordonID, int aFordonType) : fordonID(aFordonID), fordonType(aFordonType) {};
	virtual ~Fordon() { std::cout << "~Fordon" << std::endl; }
	int getFordonID() const { return fordonID; }
	int getFordonType() const { return fordonType; }
	virtual void print() = 0;
};



#endif