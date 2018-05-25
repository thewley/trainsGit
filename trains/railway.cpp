//	Jonathan Bengtsson
//	Projekt Trains V1.0
//	railway.cpp - Definitionsfil för klassen railway

#include "railway.h"
#include <fstream>
#include<sstream>
#include<algorithm>
#include"Sit_Wagon.h"
#include"Sleeping_Wagon.h"
#include"Open_Wagon.h"
#include"Covered_Wagon.h"
#include"Electric_Locomotive.h"
#include"Diesel_Locomotive.h"

Railway::Railway()
{
	vTrainStation = new std::vector<Train_Station*>;
	vTimeTable = new std::vector<TimeTable>;
}

Railway::~Railway()
{
	std::cout << tmpTs << std::endl;
	std::cout << "~Railway" << std::endl;
	for (auto &idx : *vTrainStation)
	{
		std::cout << "TRAIN_STATION IN RAILWAY : IDX : " << idx << std::endl;
		delete idx;
		idx = nullptr;
	}
	vTrainStation->clear();
	delete vTrainStation;
	delete vTimeTable;
	delete tmpTs;
}

void Railway::addTrainStation(Train_Station &ts)
{
	vTrainStation->emplace_back(&ts);
}

void Railway::print()
{
	for (auto &idx : *vTrainStation)
	{
		idx->print();
	}
}

void Railway::readTrainStations()
{


	std::string tmpStr;
	std::string name;
	int tmpID, tmpFordon, tmpSeats, tmpInet, tmpBeds, tmpCapacity, tmpSquare, tmpCubic, tmpMaxSpeed, tmpEffect, tmpFuel;
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
			ss >> tmpFordon;

			switch (tmpFordon)
			{
			case (SIT_WAGON):
				ss >> tmpSeats;
				ss >> tmpInet;
				tmpTs->addFordon(*new Sit_Wagon(tmpID, tmpInet, tmpSeats));
				//tmpTs.addToMap(tmpFordon, *new Sit_Wagon(tmpID, tmpInet, tmpSeats));
				break;
			case (SLEEPING_WAGON):
				ss >> tmpBeds;
				tmpTs->addFordon(*new Sleeping_Wagon(tmpID, tmpBeds));
				//tmpTs.addToMap(tmpFordon, *new Sleeping_Wagon(tmpID, tmpBeds));
				break;
			case (OPEN_WAGON):
				ss >> tmpCapacity;
				ss >> tmpSquare;
				tmpTs->addFordon(*new Open_Wagon(tmpID, tmpCapacity, tmpSquare));
				//tmpTs.addToMap(tmpFordon, *new Open_Wagon(tmpID, tmpCapacity, tmpSquare));
				break;
			case (COVERED_WAGON):
				ss >> tmpCubic;
				tmpTs->addFordon(*new Covered_Wagon(tmpID, tmpCubic));
				//tmpTs.addToMap(tmpFordon, *new Covered_Wagon(tmpID, tmpCubic));
				break;
			case (ELECTRIC_LOCOMOTIVE):
				ss >> tmpMaxSpeed;
				ss >> tmpEffect;
				tmpTs->addFordon(*new Electric_Locomotive(tmpID, tmpEffect, tmpMaxSpeed));
				//tmpTs.addToMap(tmpFordon, *new Electric_Locomotive(tmpID, tmpEffect, tmpMaxSpeed));
				break;
			case (DIESEL_LOCOMOTIVE):
				ss >> tmpMaxSpeed;
				ss >> tmpFuel;
				tmpTs->addFordon(*new Diesel_Locomotive(tmpID, tmpFuel, tmpMaxSpeed));
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
	TimeTable tt;
	std::string tmpStr;

	std::ifstream inFile;
	inFile.open("Trains.txt");

	if (!inFile.is_open())
		throw("Could not open Trains.txt");

	while (std::getline(inFile, tmpStr))
	{
		std::string time;
		std::stringstream ss(tmpStr);

		ss >> tt.trainId;
		ss >> tt.travelFrom.trainstation;
		ss >> tt.travelTo.trainstation;
		ss >> time;
		tt.travelFrom.time = timeToMin(time);
		ss >> time;
		tt.travelTo.time = timeToMin(time);
		ss >> tt.maxSpeed;
		ss.get();
		std::getline(ss, tt.fordon);

		vTimeTable->push_back(tt);
	}
}

void Railway::printTT()
{
	for (auto &idx : *vTimeTable)
	{
		std::cout << "Train id: " << idx.trainId << std::endl;
		std::cout << "Traveling from: " << idx.travelFrom.trainstation << std::endl;
		std::cout << "Dep time: " <<idx.travelFrom.time << std::endl;
		std::cout << "Traveling to: "<< idx.travelTo.trainstation << std::endl;
		std::cout << "Arrival time: " << idx.travelTo.time << std::endl;
		std::cout << "Max speed: " << idx.maxSpeed << std::endl;
	}
}

void Railway::sortTT()
{
	std::sort(vTimeTable->begin(), vTimeTable->end(), [&](const TimeTable &tt1, const TimeTable &tt2) 
	{
		return tt1.travelFrom.time < tt2.travelFrom.time;
	});
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


