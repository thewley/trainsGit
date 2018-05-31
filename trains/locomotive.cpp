#include "locomotive.h"

void Diesel_Locomotive::print()
{
	std::cout << "Diesel_Locomotive ID: " << fordonID << " fuel consumption: " << fuelConsumption << " max speed: " << maxSpeed << std::endl;
}

void Electric_Locomotive::print()
{
	std::cout << "Electric_Locomotive ID: " << fordonID << " effect: " << effect << "max_speed: " << maxSpeed << std::endl;
}