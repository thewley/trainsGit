//	Jonathan Bengtsson
//	Projekt Trains V1.0
//	Headerfil f�r Train_Stations-klassen

#include "Train_Station.h"
#include <utility>
#include <algorithm>
#include <sstream>


Train_Station::Train_Station()
{
	vTrain = new std::vector<Train*>;
	unusedFordon = new std::vector<Fordon*>;
}

Train_Station::~Train_Station()
{
	std::cout << "~Train_Station" << std::endl;
	for (auto &idx : *unusedFordon)
	{
		std::cout << "DELETE UNUSED : IDX : " << idx << std::endl;
		delete idx;
		idx = nullptr;
	}

	vTrain->clear();
	unusedFordon->clear();
	delete vTrain;
	delete unusedFordon;
	
}

bool Train_Station::assembleTrain(Train &aTrain)
{
	std::stringstream ss(aTrain.getFordonInTrain());
	int tmpType;

	while (ss >> tmpType)
	{
		auto it = std::find_if(unusedFordon->begin(), unusedFordon->end(), [&](const Fordon *vFordon)
		{
			return vFordon->getFordonType() == tmpType;
		});
		
		if (it != unusedFordon->end())
		{
			Fordon *f = *it;
			aTrain.add(*f);
			unusedFordon->erase(it);
		}
		else
		{
			aTrain.setDelay(10);
			return false;
		}
	}
	addTrain(aTrain);
	return true;
}

void Train_Station::print()
{
	std::cout << "StationName: " << stationName << std::endl;

	std::cout << "*****Trains in this station*****" << std::endl;
	for (auto &idx : *vTrain)
	{
		idx->print();
	}

	std::cout << "FordonPool: " << std::endl;
	for (auto &idx : *unusedFordon)
	{
		idx->print();
	}
}

//void Train_Station::printMap()
//{
//	std::cout << "StationName: " << stationName << std::endl;
//	for (auto &it : mFordon)
//	{
//		std::cout << it.first << std::endl;
//		it.second->print();
//	}
//}

void Train_Station::addFordon(Fordon &aFordon)
{
	unusedFordon->emplace_back(&aFordon);
}

void Train_Station::addTrain(Train & aTrain)
{
	vTrain->emplace_back(&aTrain);
}


//void Train_Station::addToMap(int ft, Fordon &aFordon)
//{
//	Fordon_Type val = static_cast<Fordon_Type>(ft);
//	mFordon.insert(std::make_pair(val, &aFordon));
//}
