#include "locomotive.h"

void Diesel_Locomotive::print()
{
	std::cout << "Im a Diesel_Locomotive with the ID " << fordonID << " and the fuel consumption " << fuelConsumption << " and the max speed " << maxSpeed << std::endl;
}

void Electric_Locomotive::print()
{
	std::cout << "Im a Electric_Locomotive with the ID " << fordonID << " and the effect " << effect << "and the max_speed " << maxSpeed << std::endl;
}