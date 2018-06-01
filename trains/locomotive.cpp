#include "locomotive.h"

//	Printing the Dieset_Locomotive.
void Diesel_Locomotive::print()
{
	std::cout << "Diesel_Locomotive ID: " << fordonID << " fuel consumption: " << fuelConsumption << " max speed: " << maxSpeed << std::endl;
}

//	Printing the Electric_Locomotive.
void Electric_Locomotive::print()
{
	std::cout << "Electric_Locomotive ID: " << fordonID << " effect: " << effect << " max_speed: " << maxSpeed << std::endl;
}