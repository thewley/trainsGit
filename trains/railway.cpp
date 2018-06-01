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

//	Constructor, reading all the files and opening the trainsim.log
Railway::Railway()
	:currentTime(0)
{
	std::ofstream of("trainsim.log");
	vTrainStations = new Event::TrainStations;
	vEventFinished = new std::vector<std::shared_ptr<Event>>;
	eventQueue = new Event::EventPrioQ;
	theTrainMap = new Train_Map;

	readTrainStations();
	readTrains();
}

//	Destructor
Railway::~Railway()
{
	vTrainStations->clear();
	delete vTrainStations;
	delete vEventFinished;
	delete tmpTs;
	delete eventQueue;
	delete theTrainMap;
}

//	Placing a trainstation in the TrainStation vector.
void Railway::addTrainStation(Train_Station &ts)
{
	vTrainStations->emplace_back(&ts);
}

//	Printing the names of all train stations.
void Railway::printTrainStationNames()
{
	for (auto &idx : *vTrainStations)
	{
		std::cout << idx->getTrainStationName() << std::endl;
	}
}

//	Reading the file trainstations.txt, placing all the different types of Fordon in the right trainstation.
void Railway::readTrainStations()
{


	std::string tmpStr;
	std::string name;
	int tmpID, tmpType, tmpSeats, tmpInet, tmpBeds, tmpCapacity, tmpSquare, tmpCubic, tmpMaxSpeed, tmpEffect, tmpFuel;
	bool moreToRead;
	bool readInFile = true;
	std::ifstream inFile;
	//	Open and checking the file, so its OK.
	inFile.open("TrainStations.txt");

	if (!inFile.is_open())
		throw("Cant open TrainStations.txt");


	//	Reading one line, creating that trainstation with all type of Fordons that are in the pool for that station.
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
				break;
			case (SLEEPING_WAGON):
				ss >> tmpBeds;
				tmpTs->addFordon(*new Sleeping_Wagon(tmpID, tmpType, tmpBeds));
				break;
			case (OPEN_WAGON):
				ss >> tmpCapacity;
				ss >> tmpSquare;
				tmpTs->addFordon(*new Open_Wagon(tmpID, tmpType, tmpCapacity, tmpSquare));
				break;
			case (COVERED_WAGON):
				ss >> tmpCubic;
				tmpTs->addFordon(*new Covered_Wagon(tmpID, tmpType, tmpCubic));
				break;
			case (ELECTRIC_LOCOMOTIVE):
				ss >> tmpMaxSpeed;
				ss >> tmpEffect;
				tmpTs->addFordon(*new Electric_Locomotive(tmpID, tmpType, tmpEffect, tmpMaxSpeed));
				break;
			case (DIESEL_LOCOMOTIVE):
				ss >> tmpMaxSpeed;
				ss >> tmpFuel;
				tmpTs->addFordon(*new Diesel_Locomotive(tmpID, tmpType, tmpFuel, tmpMaxSpeed));
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

//	Reading the trains.txt file, creating new Not_Assembled events and placing them in the priority queue.
void Railway::readTrains()
{
	
	std::string tmpStr;

	//	Opening and checking the file
	std::ifstream inFile;
	inFile.open("Trains.txt");
	if (!inFile.is_open())
		throw("Could not open Trains.txt");

	//	Reading one line, and placing all the information into a new train and a new Not_assembled event. 
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
		TimeTable tt;
		tt.trainID = trainId;
		tt.travelTo = travelTo;
		tt.travelFrom = travelFrom;
		vTimeTable.emplace_back(tt);
		scheduleEvent(new Not_Assembled(time, new Train(trainId, maxSpeed, travelFrom, travelTo, fordon), eventQueue, vTrainStations));
		
	}	
}

//	Printing the first event in the queue
void Railway::printFirstInQueue()
{
	std::shared_ptr<Event> ev = eventQueue->top();
	eventQueue->pop();
	ev->print(info);
}

//	Placing an event into the eventQueue.
void Railway::scheduleEvent(Event *newEvent)
{
	eventQueue->emplace(newEvent);
}

//	Converting the time HH:MM into an int.
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

//	Creating the simulation menu.
void Railway::simMenu()
{
	char choice;
	std::string tmpS;
	bool doMenu = true;
	startOfSim = false;
	do
	{
		std::cout << "1. Choose interval ["; timeToHandM(interval); std::cout << "]" << std::endl;
		std::cout << "2. Run next interval" << std::endl;
		std::cout << "3. Run next event" << std::endl;
		std::cout << "4. Finish simulation" << std::endl;
		std::cout << "5. change log level [" << ENUM_INFORMATION[info] << "]" << std::endl;
		std::cout << "6. Train menu" << std::endl;
		std::cout << "7. Station menu" << std::endl;
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
			interval = endTime - currentTime;
			doMenu = false;
			break;
		case '5':
			changeInfo();
			break;
		case '6':
			trainMenu();
			break;
		case '7':
			stationMenu();
			break;
			break;
		case '0':
			doMenu = false;
			break;
		default:
			break;
		}
	} while (doMenu);
	
}

//	Menu to change the log-information
void Railway::changeInfo()
{
	bool doMenu = true;
	do
	{
		char choice;
		std::cout << "Change LOG level" << std::endl;
		std::cout << "1. LOW info" << std::endl;
		std::cout << "2. High info" << std::endl;
		std::cout << "0. Back" << std::endl;
		std::cin >> choice;
		std::cin.get();

		switch (choice)
		{
		case '1':
			info = LOW;
			std::cout << "Log level changed to low" << std::endl;
			doMenu = false;
			break;
		case '2':
			info = HIGH;
			std::cout << "Log level changed to high" << std::endl;
			doMenu = false;
			break;
		case '0':
			doMenu = false;
			break;
		default:
			break;
		}
	} while (doMenu);
}

//	Menu to handle a train.
void Railway::trainMenu()
{
	char choice;
	std::string tmpID;
	std::cout << "1. Search train by number" << std::endl;
	std::cout << "2. Show timetable " << std::endl;
	std::cout << "3. Change log level [" << info << "]" << std::endl;
	std::cout << "0. Back" << std::endl;
	std::cin >> choice;
	std::cin.get();

	switch (choice)
	{
	case '1':
		std::cout << "Train number: ";
		getline(std::cin, tmpID);
		printTrain(tmpID);
		break;
	case '2':
		showTimeTable();
		break;
	case '3':
		changeInfo();
		break;
	case '0':
		break;
	default:
		break;
	}
}

//	Printing a train, with the right ID, if it exists.
void Railway::printTrain(std::string trainID)
{
	bool trainFound = false;
	for (auto &idx : *vTrainStations)
	{
		if (idx->findTrain(trainID, info))
			trainFound = true;
	}
	if (!trainFound)
		std::cout << "Could not find the train with the ID: " << trainID << ". Maybe its no assembled yet." << std::endl;
}

//	Printing the time table, from the time where the sim currently is at.
void Railway::showTimeTable()
{
	int currT = 0;
	std::cout << "***Time table***" << std::endl;
	
	for (auto idx : vTimeTable)
	{
		if (idx.travelTo.time > currentTime)
		{
			std::cout << "Train " << idx.trainID << " from " << idx.travelFrom.trainstation << " ";
			timeToHandM(idx.travelFrom.time);
			std::cout << std::endl << "to " << idx.travelTo.trainstation << " ";
			timeToHandM(idx.travelTo.time);
			std::cout << std::endl;
		}
	}
}

//	Showing the station menu. 
void Railway::stationMenu()
{
	char choice;
	bool doMenu = true;
	std::string tmpS;
	do
	{
		std::cout << "1. Show station names" << std::endl;
		std::cout << "2. Show station by name" << std::endl;
		std::cout << "3. Show ALL stations [HIGH]" << std::endl;
		std::cout << "0. Back" << std::endl;
		std::cin >> choice;
		std::cin.get();
		switch (choice)
		{
		case '1':
			printTrainStationNames();
			break;
		case '2':
			//	Printing one station, with all the information about that station. you need the right spelling and capital letters.
			std::cout << "Enter station name: ";
			getline(std::cin, tmpS);
			if(printStation(tmpS))
			{
				doMenu = false;
			}
			else
			{
				std::cout << "No station with that name." << std::endl;
			}
			break;
		case '3':
			//	Printing all the stations, with the Fordon and Trains in it, high volume.
			for (auto idx : *vTrainStations)
			{
				idx->print();
			}
			break;
		case '0':
			doMenu = false;
		default:
			break;
		}
	} while (doMenu);
}

//	Printing one station, depending on the stationName. 
bool Railway::printStation(std::string stationName)
{
	auto it = std::find_if(vTrainStations->begin(), vTrainStations->end(), [&](std::shared_ptr<Train_Station> ts)
	{
		return stationName == ts->getTrainStationName();
	});
	if (it != vTrainStations->end())
	{
		size_t index = std::distance(vTrainStations->begin(), it);
		vTrainStations->at(index)->print();
		return true;
	}
	else
		return false;
}

//	Running one event, only showing if its not the start of the sim.
void Railway::runEvent()
{
	std::shared_ptr<Event> ev = eventQueue->top();
	eventQueue->pop();
	currentTime = ev->getTime();
	//	If the user decides to start later that 00:00, it wont show the events before the user input startTime.
	if (!startOfSim)
	{
		timeToHandM(currentTime);
		std::cout << " ";
		ev->print(info);
	}
	ev->processEvent();
}

//	Main run loop, from start of the sim to the end with a printing result.
void Railway::run()
{
	int cTime = 0;
	int startTime = 0;
	char choice;
	bool doMenu = true;
	std::string tmpS;
	std::vector<Train> finishedTrains;

	//	First menu.
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

	//	Doing all the events that are placed betweeen (00:00 and 23:59)
	//	Not for the higher grade, no delay counted.
	for (size_t i = 0; i < endTime;)
	{
		//	Only showing the cTime(current time) after the users startTime.
		if (i >= startTime)
		{
			timeToHandM(cTime);
			std::cout << std::endl;
			simMenu();
		}
		
		// Printing one interval.
		for (size_t j = 0; j < interval; j++)
		{		
			std::shared_ptr<Event> ev = eventQueue->top();

			while (ev->getTime() == cTime)
			{
				runEvent();
				ev = eventQueue->top();
			}
				cTime++;
				i++;
		}
	}	

	//	Statistics, What trains arrived in time.
	std::cout << "Trains that arrived in time: " << std::endl;
	for (auto idx : *vTrainStations)
	{
		idx->printTrains(FINISHED);
		std::cout << std::endl;
	}

	//	Statistics, What trains arrived in time but didnt deassemble the current day.
	std::cout << "Trains that arrived in time but didnt deassemble: " << std::endl;
	for (auto idx : *vTrainStations)
	{
		idx->printTrains(ARRIVED);
		std::cout << std::endl;
	}

	//	Statistic, What trains could not assemble. 
	std::cout << std::endl << "Trains that are INCOMPLETE: " << std::endl;
	for (auto idx : *vTrainStations)
	{
		idx->printTrains(INCOMPLETE);
		std::cout << std::endl;
	}

}


