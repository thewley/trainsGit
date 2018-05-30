//	Jonathan Bengtsson
//	Projekt Trains V1.0
//	Headerfil för wagon

#ifndef WAGON_H
#define WAGON_H

#include"fordon.h"

class Wagon : public Fordon
{
public:
	Wagon(int aFordonID,int aFordonType ) : Fordon::Fordon(aFordonID, aFordonType) {};
	// Inherited via Fordon
	virtual void print() =0;
};

class Sit_Wagon : public Wagon
{
private:
	bool internet;
	int nrOfSeats;

public:

	Sit_Wagon(int aFordonID, int aFordonType, bool aInternet, int aNrOfSeats) : internet(aInternet), nrOfSeats(aNrOfSeats), Wagon::Wagon(aFordonID, aFordonType) {};

	// Inherited via Wagon
	virtual void print() override;

};

class Sleeping_Wagon : public Wagon
{
private:
	int nrOfBeds;

public:
	Sleeping_Wagon(int aFordonID, int aFordonType, int aNrOfBeds) : nrOfBeds(aNrOfBeds), Wagon::Wagon(aFordonID, aFordonType) { std::cout << "Sleeping_Wagon" << std::endl; };

	// Inherited via Wagon
	virtual void print() override;
};


class Open_Wagon : public Wagon
{
private:

	float capacity;
	float area;

public:

	Open_Wagon(int aFordonID, int aFordonType, float aCapacity, float aArea) :capacity(aCapacity), area(aArea), Wagon::Wagon(aFordonID, aFordonType) { std::cout << "Open_Wagon" << std::endl; };

	// Inherited via Wagon
	virtual void print() override;

};


class Covered_Wagon : public Wagon
{
private:
	float area;
public:
	Covered_Wagon(int aFordonID, int aFordonType, float aArea) :area(aArea), Wagon::Wagon(aFordonID, aFordonType) { std::cout << "Covered_Wagon" << std::endl; };

	// Inherited via Wagon
	virtual void print() override;

};

#endif