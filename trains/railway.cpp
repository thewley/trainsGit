//	Jonathan Bengtsson
//	Projekt Trains V1.0
//	railway.cpp - Definitionsfil för klassen railway

#include "railway.h"
#include "Event.h"
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
	std::ofstream of("finishedtrains.txt");
	vTrainStations = new Event::TrainStations;
	vEvent = new std::vector<Event>;
	eventQueue = new Event::EventPrioQ;
	theTrainMap = new Train_Map;

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
	
	vTrainStations->clear();
	delete vTrainStations;
	delete vEvent;
	delete tmpTs;
	delete eventQueue;
	delete theTrainMap;
}

void Railway::addTrainStation(Train_Station &ts)
{
	vTrainStations->emplace_back(&ts);
}

void Railway::print()
{
	for (auto &idx : *vTrainStations)
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

		scheduleEvent(new Not_Assembled(time, new Train(trainId, maxSpeed, travelFrom, travelTo, fordon), eventQueue, vTrainStations));
		
		
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

void Railway::doMenuTwo()
{
	char choice;
	std::string tmpS;
	bool doMenu = true;

	do
	{
		std::cout << "1. Choose interval ["; timeToHandM(interval); std::cout << "]" << std::endl;
		std::cout << "2. Run next interval" << std::endl;
		std::cout << "3. Run next event" << std::endl;
		std::cout << "4. Finish simulation" << std::endl;
		std::cout << "5. change log level: " << std::endl;
		std::cout << "6. Train menu" << std::endl;
		std::cout << "7. Station menu" << std::endl;
		std::cout << "8. Vehicle menu" << std::endl;
		std::cout << "0. Exit" << std::endl;
		std::cin >> choice;
		std::cin.get();

		switch (choice)
		{
		case '1':
			std::cout << "Choose interval time [(H)H:MM] : ";
			getline(std::cin, tmpS);
			interval = timeToMin(tmpS);
			break;
		case '2':
			doMenu = false;
			break;
		case '3':
			runEvent();
			break;
		case '4':
			interval = TOTAL_SIM_TIME - currentTime;
			doMenu = false;
			break;
		case '5':
			break;
		case '6':
			break;
		case '7':
			break;
		case '8':
			break;
		case '0':
			break;
		default:
			break;
		}
	} while (doMenu);
	
}

void Railway::runEvent()
{
	std::shared_ptr<Event> ev = eventQueue->top();
	eventQueue->pop();
	currentTime = ev->getTime();
	ev->processEvent();
}

void Railway::run()
{
	int cTime = 0;
	int startTime = 0;
	int endTime = 1439;
	char choice;
	bool doMenu = true;
	std::string tmpS;
	std::vector<Train> finishedTrains;

	do
	{
		std::cout << "1. choose your start time currently: "; timeToHandM(startTime); std::cout << std::endl;
		std::cout << "2. choose your end time currently: "; timeToHandM(endTime); std::cout << std::endl;
		std::cout << "3. start sim" << std::endl;
		std::cin >> choice;
		std::cin.get();
		switch (choice)
		{
		case '1':
			std::cout << "Choose start time [(H)H:MM] : ";
			getline(std::cin, tmpS);
			startTime = timeToMin(tmpS);
			break;
		case '2':
			std::cout << "Choose end time [(H)H:MM] : ";
			getline(std::cin, tmpS);
			endTime = timeToMin(tmpS);
			break;
		case '3':
			std::cout << "Starting Simulation!" << std::endl;
			doMenu = false;
			break;
		default:
			break;
		}

	} while (doMenu);

	for (size_t i = 0; i < endTime;)
	{
		if (i >= startTime)
		{
			timeToHandM(cTime);
			std::cout << std::endl;
			doMenuTwo();
		}
		
		for (size_t j = 0; j < interval; j++)
		{		
			std::shared_ptr<Event> ev = eventQueue->top();
			while (ev->getTime() == cTime)
			{
				eventQueue->pop();
				currentTime = ev->getTime();
				std::cout << "Time: "; timeToHandM(currentTime); std::cout << std::endl;
				//ev->print();
				ev->processEvent();
				ev = eventQueue->top();
				
			}
				cTime++;
				i++;
		}
	}	

}


