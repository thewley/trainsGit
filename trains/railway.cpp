//	Jonathan Bengtsson
//	Projekt Trains V1.0
//	railway.cpp - Definitionsfil för klassen railway

#include "railway.h"
#include <fstream>
#include<sstream>
#include<algorithm>
#include"Wagon.h"
#include"locomotive.h"

Railway::Railway()
	:currentTime(0)
{
	//new
	/*vTrainStation = new std::vector<Train_Station*>;*/
	
	vTrainStation = new std::vector<std::shared_ptr<Train_Station>>;
	vEvent = new std::vector<Event>;
	eventQueue = new std::priority_queue<std::shared_ptr<Event>, std::vector<std::shared_ptr<Event>>, TimeComparison>;

	readTrainStations();
	readTrains();
}

Railway::~Railway()
{
	std::cout << tmpTs << std::endl;
	std::cout << "~Railway" << std::endl;

	//new
	//for (auto &idx : *vTrainStation)
	//{
	//	std::cout << "TRAIN_STATION IN RAILWAY : IDX : " << idx << std::endl;
	//	delete idx;
	//	idx = nullptr;
	//}
	
	vTrainStation->clear();
	delete vTrainStation;
	delete vEvent;
	delete tmpTs;
	delete eventQueue;
}

void Railway::addTrainStation(Train_Station &ts)
{
	vTrainStation->emplace_back(&ts);
}

void Railway::print()
{
	for (auto &idx : *vTrainStation)
	{
		//idx->print();
		std::cout << idx->getTrainStationName() << std::endl;
	}
}

void Railway::readTrainStations()
{


	std::string tmpStr;
	std::string name;
	int tmpID, tmpType, tmpSeats, tmpInet, tmpBeds, tmpCapacity, tmpSquare, tmpCubic, tmpMaxSpeed, tmpEffect, tmpFuel;
	bool moreToRead;
	bool readInFile = true;
	std::ifstream inFile;
	inFile.open("TrainStations.txt");

	if (!inFile.is_open())
		throw("Cant open TrainStations.txt");


	
	while (std::getline(inFile, tmpStr))
	{

		tmpTs = new Train_Station;
		moreToRead = true;
		std::size_t found = tmpStr.find_last_of(")");
		tmpStr.erase(found);
		tmpStr.erase(std::remove(tmpStr.begin(), tmpStr.end(), '('), tmpStr.end());
		std::replace(tmpStr.begin(), tmpStr.end(), ')', ' ');
		std::stringstream ss(tmpStr);
	
		ss >> name;
		tmpTs->setStationName(name);
		while (moreToRead)
		{
			ss >> tmpID;
			ss >> tmpType;

			switch (tmpType)
			{
			case (SIT_WAGON):
				ss >> tmpSeats;
				ss >> tmpInet;
				tmpTs->addFordon(*new Sit_Wagon(tmpID, tmpType, tmpInet, tmpSeats));
				//tmpTs.addToMap(tmpFordon, *new Sit_Wagon(tmpID, tmpInet, tmpSeats));
				break;
			case (SLEEPING_WAGON):
				ss >> tmpBeds;
				tmpTs->addFordon(*new Sleeping_Wagon(tmpID, tmpType, tmpBeds));
				//tmpTs.addToMap(tmpFordon, *new Sleeping_Wagon(tmpID, tmpBeds));
				break;
			case (OPEN_WAGON):
				ss >> tmpCapacity;
				ss >> tmpSquare;
				tmpTs->addFordon(*new Open_Wagon(tmpID, tmpType, tmpCapacity, tmpSquare));
				//tmpTs.addToMap(tmpFordon, *new Open_Wagon(tmpID, tmpCapacity, tmpSquare));
				break;
			case (COVERED_WAGON):
				ss >> tmpCubic;
				tmpTs->addFordon(*new Covered_Wagon(tmpID, tmpType, tmpCubic));
				//tmpTs.addToMap(tmpFordon, *new Covered_Wagon(tmpID, tmpCubic));
				break;
			case (ELECTRIC_LOCOMOTIVE):
				ss >> tmpMaxSpeed;
				ss >> tmpEffect;
				tmpTs->addFordon(*new Electric_Locomotive(tmpID, tmpType, tmpEffect, tmpMaxSpeed));
				//tmpTs.addToMap(tmpFordon, *new Electric_Locomotive(tmpID, tmpEffect, tmpMaxSpeed));
				break;
			case (DIESEL_LOCOMOTIVE):
				ss >> tmpMaxSpeed;
				ss >> tmpFuel;
				tmpTs->addFordon(*new Diesel_Locomotive(tmpID, tmpType, tmpFuel, tmpMaxSpeed));
				//tmpTs.addToMap(tmpFordon, *new Diesel_Locomotive(tmpID, tmpFuel, tmpMaxSpeed));
				break;
			default:
				break;
			}
			if (ss.eof())
				moreToRead = false;

		}
		addTrainStation(*tmpTs);
		tmpTs = nullptr;
	}
}

void Railway::readTrains()
{
	
	std::string tmpStr;

	std::ifstream inFile;
	inFile.open("Trains.txt");

	if (!inFile.is_open())
		throw("Could not open Trains.txt");

	while (std::getline(inFile, tmpStr))
	{
		
		int time;
		int trainId, maxSpeed;
		Travel travelFrom, travelTo;
		std::string fromTime, toTime, fordon;
		std::stringstream ss(tmpStr);
		
		ss >> trainId;
		ss >> travelFrom.trainstation;
		ss >> travelTo.trainstation;
		ss >> fromTime;
		travelFrom.time = timeToMin(fromTime);
		ss >> toTime;
		travelTo.time = timeToMin(toTime);
		ss >> maxSpeed;
		ss.get();
		std::getline(ss, fordon);

		time = timeToMin(fromTime) - TIME_TO_ASSEMBLE;


		scheduleEvent(new Not_Assembled(time, new Train(trainId, maxSpeed, travelFrom, travelTo, fordon)));
		
		
	}	
}

void Railway::printFirstInQueue()
{
	std::shared_ptr<Event> ev = eventQueue->top();
	eventQueue->pop();
	ev->print();
}

void Railway::scheduleEvent(Event *newEvent)
{
	eventQueue->emplace(newEvent);
}

int Railway::timeToMin(std::string &aString)
{
	int totTime, tmpH, tmpM;
	std::replace(aString.begin(), aString.end(), ':', ' ');
	std::stringstream ss(aString);
	ss >> tmpH;
	ss >> tmpM;
	totTime = tmpH * 60 + tmpM;
	return totTime;
}

void Railway::run()
{
	while (!eventQueue->empty())
	{
	std::shared_ptr<Event> ev = eventQueue->top();
	eventQueue->pop();
	currentTime = ev->getTime();
	ev->processEvent(*vTrainStation);
	}
}


