//	Jonathan Bengtsson
//	Projekt Trains V1.0
//	Headerfil för diesel-locomotive

#ifndef DIESE_LOCOMOTIVE_H
#define DIESE_LOCOMOTIVE_H

#include"locomotive.h"

class Diesel_Locomotive : public Locomotive
{
private:
	float fuelConsumption;

public:

	Diesel_Locomotive(int aFordonID, float aFuelConsumption, float aMaxSpeed) : fuelConsumption(aFuelConsumption), Locomotive::Locomotive(aFordonID, aMaxSpeed) { std::cout << "Diesel_Locomotive skapas" << std::endl; };

	// Inherited via Locomotive
	virtual void print() override;

};

#endif