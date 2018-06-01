//	Jonathan Bengtsson
//	Projekt Trains V1.0
//	Headerfil för Train_Stations-klassen

#include "Train_Station.h"
#include <utility>
#include <algorithm>
#include <sstream>

//	Constructor
Train_Station::Train_Station()
{
	vTrain = new std::vector<Train*>;
	unusedFordon = new std::vector<Fordon*>;
}

//	Destructor
Train_Station::~Train_Station()
{
	for (auto &idx : *unusedFordon)
	{
		delete idx;
		idx = nullptr;
	}

	vTrain->clear();
	unusedFordon->clear();
	delete vTrain;
	delete unusedFordon;
	
}

//	Assemble a train from the trainstation.
bool Train_Station::assembleTrain(Train &aTrain)
{
	//	Getting what types of fordon the train will contain
	std::stringstream ss(aTrain.getFordonInTrain());
	int tmpType;

	//	While there is more to read.
	while (ss >> tmpType)
	{
		//	Trying to find the right type of fordon in the vector.
		auto it = std::find_if(unusedFordon->begin(), unusedFordon->end(), [&](const Fordon *vFordon)
		{
			return vFordon->getFordonType() == tmpType;
		});

		size_t index = std::distance(unusedFordon->begin(), it);

		//	If there still is a correct type left in the vector, adding it to the train and deleting it from the fordonpool.
		if (it != unusedFordon->end())
		{
			aTrain.add(unusedFordon->at(index));
			unusedFordon->erase(it);
		}
		//	If there is not a correct type of Fordon left in the pool, changing the string in the used fordon and adding the train to the station(getting incomplete), returning false.
		else
		{
			std::string tmpString;
			std::getline(ss, tmpString);
			std::string newFordonInTrain = std::to_string(tmpType) + " " + tmpString;
			
			aTrain.setFordonInTrain(newFordonInTrain);
			addTrain(&aTrain);
			return false;
		}
	}
	addTrain(&aTrain);
	return true;
}

//	Deassemble train at this trainstation.
bool Train_Station::deassembleTrain(Train & aTrain)
{
	//	Deassemble the train and placing all the fordon in the pool.
	for (auto idx : aTrain.getVFordon())
	{
		unusedFordon->emplace_back(idx);
	}
	aTrain.clearVFordon();
	//	Sorting the pool on ID, so the fordon with lowest ID will be used first.
	std::sort(unusedFordon->begin(), unusedFordon->end(), [](const Fordon *left, const Fordon *right) 
	{
		return left->getFordonID() < right->getFordonID();
	});

	return true;
}

//	Printing a trainstation.
void Train_Station::print()
{
	std::cout << "StationName: " << stationName << std::endl;

	std::cout << "*****Trains in this station*****" << std::endl;
	for (auto &idx : *vTrain)
	{
		idx->print(HIGH);
	}

	std::cout << "FordonPool: " << std::endl;
	for (auto &idx : *unusedFordon)
	{
		idx->print();
	}
}

//	Printing the trains in the station.
void Train_Station::printTrains(State state)
{
	for (auto idx : *vTrain)
	{
		if (idx->getState() == state)
		{
			idx->print();
		}
	}

}

//	Adding a fordon to the pool
void Train_Station::addFordon(Fordon &aFordon)
{
	unusedFordon->emplace_back(&aFordon);
}

//	Adding a train to the station.
void Train_Station::addTrain(Train *aTrain)
{
	vTrain->emplace_back(aTrain);
}

//	Removing a train from the station.
bool Train_Station::removeTrain(int id)
{
	auto it = std::find_if(vTrain->begin(), vTrain->end(), [&](Train *train) 
	{
		return train->getTrainID() == id;
	});
	
	if (it != vTrain->end())
	{
		vTrain->erase(it);
		return true;
	}
	else
		return false;
}

//	Finding a train at the station. returning true if the train is in the station, otherwise false.
bool Train_Station::findTrain(std::string trainID, Information info)
{
	auto it = std::find_if(vTrain->begin(), vTrain->end(), [&](const Train *t) 
	{
		return t->getTrainID() == std::stoi(trainID);
	});

	size_t index = std::distance(vTrain->begin(), it);

	if (it != vTrain->end())
	{
		vTrain->at(index)->print(info);
		return true;
	}
	return false;
}
