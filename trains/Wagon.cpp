#include "Wagon.h"

void Sit_Wagon::print()
{
	std::cout << "Im a Sit_Wagon with the ID " << fordonID << " and internet " << std::boolalpha << internet << " and the nrOfSeats " << nrOfSeats << std::endl;
}

void Sleeping_Wagon::print()
{
	std::cout << "Im a Sleeping_Wagon with the ID " << fordonID << " and the nrOfBeds " << nrOfBeds << std::endl;
}

void Covered_Wagon::print()
{
	std::cout << "Im a Covered_Wagon with the ID " << fordonID << " and the area " << area << std::endl;
}

void Open_Wagon::print()
{
	std::cout << "Im an open_wagon with the ID " << fordonID << " and the capacity " << capacity << " and the area " << area << std::endl;
}
