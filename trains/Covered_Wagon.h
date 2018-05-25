//	Jonathan Bengtsson
//	Projekt Trains V1.0
//	Headerfil för Covered_Wagon

#ifndef COVERED_WAGON_H
#define COVERED_WAGON_H

#include"Wagon.h"

class Covered_Wagon : public Wagon
{
private:
	float area;
public:
	Covered_Wagon(int aFordonID, float aArea) :area(aArea), Wagon::Wagon(aFordonID) { std::cout << "Covered_Wagon" << std::endl; };

	// Inherited via Wagon
	virtual void print() override;

};

#endif