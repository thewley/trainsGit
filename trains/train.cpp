//	Jonathan Bengtsson
//	Projekt Trains V1.0
//	Train.cpp - Definitionsfil för Train-klassen

#include "train.h"
#include <iomanip>
#include <string>

//	Constructor.
Train::Train()
	:trainID(0), trainNumber(0), delay(0), avarageSpeed(0), state(NOT_ASSEMBLED)
{
	vFordon = new std::vector<Fordon*>;
	travelFrom.trainstation = "";
	travelFrom.time = 0;
	travelTo.trainstation = "";
	travelTo.time = 0;
}

//	Constructor
Train::Train(int aTrainID, double aMaxSpeed, Travel aTravelFrom, Travel aTravelTo, std::string aFordonInTrain)
	:trainID(aTrainID), maxSpeed(aMaxSpeed), travelFrom(aTravelFrom), travelTo(aTravelTo), fordonInTrain(aFordonInTrain)
{ 
	state = NOT_ASSEMBLED;
	vFordon = new std::vector<Fordon*>; 
}

//	Destructor
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

//	Adding a Fordon to a train.
void Train::add(Fordon *aFordon)
{
	vFordon->emplace_back(aFordon);
}

//	Print function for a train.
void Train::print(Information info)
{
	//	Depending on what info the user wanna show.
	if (info == HIGH)
	{
		std::cout << "Train [" << trainID << "]" << "(" << ENUM_STATE[state] << ")"
		<< " from " << travelFrom.trainstation << " "; timeToHandM(travelFrom.time);
		std::cout << " to: " << travelTo.trainstation<< " "; timeToHandM(travelTo.time + delay); std::cout << std::endl;

		for (auto &idx : *vFordon)
			idx->print();
	}
	else
	{
		std::cout << "Train ID: " << trainID << " ";
		std::cout << "State: " << ENUM_STATE[state] << std::endl;
	}
}

//	Printing only the train ID.
void Train::print()
{
	std::cout << trainID << " ";
}

//	Help functions
//	converting a int to a time, HH:MM and printing it.
void timeToHandM(int time)
{
	int hour{ 0 }, min{ 0 };

	hour = time / 60;
	min = time % 60;

	std::cout << std::setw(2) << std::setfill('0') << hour << ":" << std::setw(2) << std::setfill('0') << min;

}

//	Converting the hour in a time and returning it as a string.
std::string toHour(int time)
{
	int hour{ 0 };
	std::string tmpH;

	hour = time / 60;

	tmpH = std::to_string(hour);

	return tmpH;
}

//	Converting the minutes in a time and returnging it as a string.
std::string toMin(int time)
{
	int min{ 0 };
	std::string tmpMin;

	min = time % 60;
	tmpMin = std::to_string(min);

	return tmpMin;
}
