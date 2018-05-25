//	Jonathan Bengtsson
//	Projekt Trains V1.0
//	Electric_Locomotive.cpp - Definitionsfil för Electric_Locomotive-klassen

#include "Electric_Locomotive.h"

void Electric_Locomotive::print()
{
	std::cout << "Im a Electric_Locomotive with the ID " << fordonID << " and the effect " << effect << "and the max_speed " << maxSpeed << std::endl;
}
