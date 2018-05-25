//	Jonathan Bengtsson
//	Projekt Trains V1.0
//	Headerfil för Sit_Wagon

#ifndef SIT_WAGON_H
#define SIT_WAGON_H

#include"Wagon.h"

class Sit_Wagon : public Wagon
{
private:
	bool internet;
	int nrOfSeats;

public:

	Sit_Wagon(int aFordonID, bool aInternet, int aNrOfSeats) : internet(aInternet), nrOfSeats(aNrOfSeats), Wagon::Wagon(aFordonID) {};

	// Inherited via Wagon
	virtual void print() override;

};

#endif