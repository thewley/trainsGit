//	Jonathan Bengtsson
//	Projekt Trains V1.0
//	Diesel_Locomotive.cpp - Definitionsfil för Diesel_Locomotive-klassen

#include "Diesel_Locomotive.h"

void Diesel_Locomotive::print()
{
	std::cout << "Im a Diesel_Locomotive with the ID " << fordonID <<" and the fuel consumption " << fuelConsumption << " and the max speed " << maxSpeed << std::endl;
}
