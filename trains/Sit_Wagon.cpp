//	Jonathan Bengtsson
//	Projekt Trains V1.0
//	Sit_Wagon.cpp - Definitionsfil för Sit_Wagon-klassen

#include "Sit_Wagon.h"

void Sit_Wagon::print()
{
	std::cout << "Im a Sit_Wagon with the ID " << fordonID << " and internet " << std::boolalpha << internet << " and the nrOfSeats " << nrOfSeats << std::endl;
}
