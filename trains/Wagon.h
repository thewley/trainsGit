//	Jonathan Bengtsson
//	Projekt Trains V1.0
//	Headerfil för wagon

#ifndef WAGON_H
#define WAGON_H

#include"fordon.h"

class Wagon : public Fordon
{
public:
	Wagon(int aFordonID) : Fordon::Fordon(aFordonID) {};
	// Inherited via Fordon
	virtual void print() =0;
};

#endif