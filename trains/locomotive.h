//	Jonathan Bengtsson
//	Projekt Trains V1.0
//	Headerfil för locomotive

#ifndef LOCOMOTIVE_H
#define LOCOMOTIVE_H

#include "fordon.h"

class Locomotive : public Fordon
{
protected:
	float maxSpeed;

public:
	
	Locomotive(int aFordonID, float aMaxSpeed) :maxSpeed(aMaxSpeed), Fordon::Fordon(aFordonID){ std::cout << "Locomotive skapas" << std::endl; };
	
	float getMaxSpeed() { return maxSpeed; };

	virtual void print() = 0;


};

#endif