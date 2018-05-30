//	Jonathan Bengtsson
//	Projekt Trains V1.0
//	Train.cpp - Definitionsfil för Train-klassen

#include "train.h"

Train::Train()
	:trainID(0), trainNumber(0), delay(0), avarageSpeed(0), state(NOT_ASSEMBLED)
{
	vFordon = new std::vector<Fordon*>;
	travelFrom.trainstation = "";
	travelFrom.time = 0;
	travelTo.trainstation = "";
	travelTo.time = 0;
}

Train::Train(int aTrainID, double aMaxSpeed, Travel aTravelFrom, Travel aTravelTo, std::string aFordonInTrain)
	:trainID(aTrainID), maxSpeed(aMaxSpeed), travelFrom(aTravelFrom), travelTo(aTravelTo), fordonInTrain(aFordonInTrain)
{ 
	state = NOT_ASSEMBLED;
	vFordon = new std::vector<Fordon*>; 
}

Train::~Train()
{
	std::cout << "~Train" << std::endl;
	for (auto &idx : *vFordon)
	{
		delete idx;
		idx = nullptr;
	}
	vFordon->clear();
	delete vFordon;
}

void Train::add(Fordon &aFordon)
{
	vFordon->emplace_back(&aFordon);
}

void Train::print()
{
	
	std::cout << "*** Train information ***" << std::endl;
	std::cout << "State: " << ENUM_STATE[state] << std::endl;
	std::cout << "Traveling from: " << travelFrom.trainstation << std::endl << "Departure Time: " << travelFrom.time << std::endl;
	std::cout << "Traveling to: " << travelTo.trainstation << std::endl << "Arrival Time: " << travelTo.time + delay << std::endl;

	for (auto &idx : *vFordon)
		idx->print();
}
