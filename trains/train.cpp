//	Jonathan Bengtsson
//	Projekt Trains V1.0
//	Train.cpp - Definitionsfil för Train-klassen

#include "train.h"
#include <iomanip>

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
	//std::cout << "~Train" << std::endl;
	for (auto &idx : *vFordon)
	{
		delete idx;
		idx = nullptr;
	}
	vFordon->clear();
	delete vFordon;
}

void Train::add(Fordon *aFordon)
{
	vFordon->emplace_back(aFordon);
}

void Train::print()
{
	
	std::cout << "*** Train information ***" << std::endl;
	std::cout << "Train ID: " << trainID << std::endl;


	std::cout << "State: " << ENUM_STATE[state] << std::endl;
	std::cout << "Traveling from: " << travelFrom.trainstation << std::endl << "Departure Time: "; timeToHandM(travelFrom.time); std::cout << std::endl;
	std::cout << "Traveling to: " << travelTo.trainstation << std::endl << "Arrival Time: "; timeToHandM(travelTo.time + delay); std::cout << std::endl;

	for (auto &idx : *vFordon)
		idx->print();
}

void timeToHandM(int time)
{
	int hour{ 0 }, min{ 0 };

	hour = time / 60;
	min = time % 60;

	std::cout << std::setw(2) << std::setfill('0') << hour << ":" << std::setw(2) << std::setfill('0') << min;

}
