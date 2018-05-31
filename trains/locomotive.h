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
	
	Locomotive(int aFordonID,int aFordonType, float aMaxSpeed) :maxSpeed(aMaxSpeed), Fordon::Fordon(aFordonID, aFordonType){ };
	
	float getMaxSpeed() { return maxSpeed; };

	virtual void print() = 0;
};

class Electric_Locomotive : public Locomotive
{
private:
	float effect;
public:
	Electric_Locomotive(int aFordonID, int aFordonType, float aEffect, float aMaxSpeed) :effect(aEffect), Locomotive::Locomotive(aFordonID, aFordonType, aMaxSpeed) { };

	// Inherited via Locomotive
	virtual void print() override;
};

class Diesel_Locomotive : public Locomotive
{
private:
	float fuelConsumption;
public:
	Diesel_Locomotive(int aFordonID, int aFordonType, float aFuelConsumption, float aMaxSpeed) : fuelConsumption(aFuelConsumption), Locomotive::Locomotive(aFordonID, aFordonType, aMaxSpeed) { };

	// Inherited via Locomotive
	virtual void print() override;

};

#endif