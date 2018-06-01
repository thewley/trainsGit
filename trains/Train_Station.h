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

//	Enum for the type of Fordon
enum Fordon_Type { SIT_WAGON, SLEEPING_WAGON, OPEN_WAGON, COVERED_WAGON, ELECTRIC_LOCOMOTIVE, DIESEL_LOCOMOTIVE };
static const char * ENUM_FORDON_TYPE[] = { "sit wagon", "sleeping wagon", "open wagon", "covered wagon","electric locomotive", "diesel locomotive" };

class Train_Station
{
private:
	std::string stationName;
	std::vector<Train*> *vTrain;
	std::vector<Fordon*> *unusedFordon;

public:

	//	Constructor and destructor
	Train_Station();
	~Train_Station();

	//	Setters and getters
	void setStationName(std::string aStationName) { stationName = aStationName; }
	std::string getTrainStationName() const { return stationName; }
	std::vector<Train*> getVTrain() const { return *vTrain; }
	
	//	Memberfunctions
	bool assembleTrain(Train &aTrain);
	bool deassembleTrain(Train &aTrain);
	void print();
	void printTrains(State state);
	void addFordon(Fordon &aFordon);
	void addTrain(Train *aTrain);
	bool removeTrain(int id);
	bool findTrain(std::string trainID, Information info);
};


#endif
