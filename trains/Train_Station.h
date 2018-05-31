//	Jonathan Bengtsson
//	Projekt Trains V1.0
//	Headerfil för Train_Stations-klassen

#ifndef TRAIN_STATION_H
#define TRAIN_STATION_H

#include"constants.h"
#include"train.h"
#include<memory>
#include<vector>
#include<string>
#include<map>

enum Fordon_Type { SIT_WAGON, SLEEPING_WAGON, OPEN_WAGON, COVERED_WAGON, ELECTRIC_LOCOMOTIVE, DIESEL_LOCOMOTIVE };
static const char * ENUM_FORDON_TYPE[] = { "sit wagon", "sleeping wagon", "open wagon", "covered wagon","electric locomotive", "diesel locomotive" };

class Train_Station
{
private:
	std::string stationName;
	std::vector<Train*> *vTrain;
	std::vector<Fordon*> *unusedFordon;
	//std::multimap<Fordon_Type, std::unique_ptr<Fordon>> mFordon;

public:

	Train_Station();
	~Train_Station();

	void setStationName(std::string aStationName) { stationName = aStationName; }
	std::string getTrainStationName() const { return stationName; }
	
	bool assembleTrain(Train &aTrain);
	bool deassembleTrain(Train &aTrain);
	void print();
	//void printMap();
	void addFordon(Fordon &aFordon);
	void addTrain(Train *aTrain);
	//void addToMap(int ft, Fordon &aFordon);
};


#endif
