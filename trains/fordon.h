//	Jonathan Bengtsson
//	Projekt Trains V1.0
//	Headerfil för fordon

#ifndef FORDON_H
#define FORDON_H

#include<iostream>

//	The Fordon class, abstract base class for all the different types of fordon
class Fordon
{
protected:
	int fordonID;
	int fordonType;

public:
	Fordon(int aFordonID, int aFordonType) : fordonID(aFordonID), fordonType(aFordonType) {};
	virtual ~Fordon() { }
	int getFordonID() const { return fordonID; }
	int getFordonType() const { return fordonType; }
	virtual void print() = 0;
};



#endif