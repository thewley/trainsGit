//	Jonathan Bengtsson
//	Projekt Trains V1.0
//	train_map.cpp - Definitionsfil för Train_Map-klassen
//	Class for higher grade.

#include "Train_Map.h"
#include <fstream>
#include<iostream>
#include<algorithm>

//	Konstruktorn för Train_Map, läser in filen TrainMap.txt och lägger in alla värden i en vector med distanser mellan två stationer.
Train_Map::Train_Map()
{
	vDistance = new std::vector<Distance>;
	bool moreToRead = true;
	Distance dist;
	std::ifstream inFile;

	inFile.open("TrainMap.txt");
	if (!inFile.is_open())
		throw std::runtime_error("Could not open TrainMap.txt");

	std::ios_base::iostate mask = std::ios::eofbit | std::ios::failbit | std::ios::badbit;
	inFile.exceptions(mask);

	//	Trying to read the trainmao.txt
	while (moreToRead)
	{
		try
		{
			inFile >> dist.stationOne;
			inFile >> dist.stationTwo;
			inFile >> dist.distance;
		}
		catch (std::ios_base::failure &eo)
		{
			std::ios_base::iostate flags = inFile.rdstate();

			if (flags & std::ios::eofbit)
			{
				inFile.clear();
				moreToRead = false;
			}
			else
			{
				std::string error;
				inFile.clear();
				getline(inFile, error);
				std::cout << error << std::endl;
			}

		}

		vDistance->push_back(dist);

	}

}

//Hjälp, skriver ut vectorn med alla stationer och avståndet mellan dem.
void Train_Map::print()
{
	for (auto &idx : *vDistance)
	{
		std::cout << "From: " << idx.stationOne << " To: " << idx.stationTwo  << " Distance: " << idx.distance << std::endl; 
	}
}

//	Returnerar avståndet mellan två tågstationer
int Train_Map::findDistance(std::string aDistanceFrom, std::string aDistanceTo)
{
	
	auto it = std::find_if(vDistance->begin(), vDistance->end(), [&](const Distance &a) 
	{
		return a.stationOne == aDistanceFrom && a.stationTwo == aDistanceTo || a.stationOne == aDistanceTo && a.stationTwo == aDistanceFrom;
	});

	int distance = it->distance;
	

	return distance;
}
