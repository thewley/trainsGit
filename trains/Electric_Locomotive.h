//	Jonathan Bengtsson
//	Projekt Trains V1.0
//	Headerfil för electric-locomotive

#ifndef ELECTRIC_LOCOMOTIVE_H
#define ELECTRIC_LOCOMOTIVE_H

#include"locomotive.h"

class Electric_Locomotive : public Locomotive
{
private:
	float effect;

public:
	Electric_Locomotive(int aFordonID, float aEffect, float aMaxSpeed) :effect(aEffect), Locomotive::Locomotive(aFordonID, aMaxSpeed) { std::cout << "Electric_Locomotive" << std::endl; };

	// Inherited via Locomotive
	virtual void print() override;
};

#endif