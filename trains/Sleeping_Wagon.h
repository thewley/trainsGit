//	Jonathan Bengtsson
//	Projekt Trains V1.0
//	Headerfil för Sleeping_Wagon

#ifndef SLEEPING_WAGON_H
#define SLEEPING_WAGON_H

#include"Wagon.h"

class Sleeping_Wagon : public Wagon
{
private:
	int nrOfBeds;

public:
	Sleeping_Wagon(int aFordonID, int aNrOfBeds) : nrOfBeds(aNrOfBeds), Wagon::Wagon(aFordonID) { std::cout << "Sleeping_Wagon" << std::endl; };

	// Inherited via Wagon
	virtual void print() override;
};
#endif