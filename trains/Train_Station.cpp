//	Jonathan Bengtsson
//	Projekt Trains V1.0
//	Headerfil för Train_Stations-klassen

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
	//std::cout << "~Train_Station" << std::endl;
	for (auto &idx : *unusedFordon)
	{
		//std::cout << "DELETE UNUSED : IDX : " << idx << std::endl;
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

		size_t index = std::distance(unusedFordon->begin(), it);

		if (it != unusedFordon->end())
		{
			//unusedFordon->at(index);
			//Fordon *f = *it;
			aTrain.add(unusedFordon->at(index));
			unusedFordon->erase(it);
		}
		else
		{
			std::string tmpString;
			std::getline(ss, tmpString);
			std::string newFordonInTrain = std::to_string(tmpType) + " " + tmpString;
			
			aTrain.setFordonInTrain(newFordonInTrain);
			return false;
		}
	}
	addTrain(&aTrain);
	return true;
}

bool Train_Station::deassembleTrain(Train & aTrain)
{
	//KOLLA PÅ DENNA, BORDE FUNGERA MEN GÖR DET NOG INTE -.-.-.-
	for (auto idx : aTrain.getVFordon())
	{
		unusedFordon->emplace_back(idx);
	}
	aTrain.clearVFordon();
	std::sort(unusedFordon->begin(), unusedFordon->end(), [](const Fordon *left, const Fordon *right) 
	{
		return left->getFordonID() < right->getFordonID();
	});

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

void Train_Station::addTrain(Train *aTrain)
{
	vTrain->emplace_back(aTrain);
}


//void Train_Station::addToMap(int ft, Fordon &aFordon)
//{
//	Fordon_Type val = static_cast<Fordon_Type>(ft);
//	mFordon.insert(std::make_pair(val, &aFordon));
//}
