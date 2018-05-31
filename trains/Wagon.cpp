#include "Wagon.h"

void Sit_Wagon::print()
{
	std::cout << "Sit_Wagon ID: " << fordonID << " internet: " << std::boolalpha << internet << " nrOfSeats: " << nrOfSeats << std::endl;
}

void Sleeping_Wagon::print()
{
	std::cout << "Sleeping_Wagon ID: " << fordonID << " nrOfBeds: " << nrOfBeds << std::endl;
}

void Covered_Wagon::print()
{
	std::cout << "Covered_Wagon ID: " << fordonID << " area: " << area << std::endl;
}

void Open_Wagon::print()
{
	std::cout << "open_wagon ID: " << fordonID << " capacity: " << capacity << " area: " << area << std::endl;
}
