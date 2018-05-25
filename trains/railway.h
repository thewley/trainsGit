//	Jonathan Bengtsson
//	Projekt Trains V1.0
//	Headerfil för klassen railway

#include"Train_Station.h"


struct TimeTable
{
	int trainId;
	Travel travelFrom;
	Travel travelTo;
	double maxSpeed;
	std::string fordon;
};

class Railway
{
private:
	std::vector<Train_Station*> *vTrainStation;
	std::vector<TimeTable> *vTimeTable;
	Train_Station *tmpTs;

public:
	Railway();
	~Railway();
	void addTrainStation(Train_Station &ts);
	void print();
	void readTrainStations();
	void readTrains();
	void printTT();
	void sortTT();
	int timeToMin(std::string &aString);
};
