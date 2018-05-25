//	Jonathan Bengtsson
//	Projekt Trains V1.0
//	Headerfil för Open_Wagon

#ifndef OPEN_WAGON_H
#define OPEN_WAGON_H

#include"Wagon.h"

class Open_Wagon : public Wagon
{
private:

	float capacity;
	float area;

public:

	Open_Wagon(int aFordonID, float aCapacity, float aArea) :capacity(aCapacity), area(aArea), Wagon::Wagon(aFordonID) { std::cout << "Open_Wagon" << std::endl; };

	// Inherited via Wagon
	virtual void print() override;

};

#endif