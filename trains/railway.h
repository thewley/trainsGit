//	Jonathan Bengtsson
//	Projekt Trains V1.0
//	Headerfil för klassen railway

#ifndef RAILWAY_H
#define RAILWAY_H

#include"Train_Station.h"
#include"Event.h"

#include<memory>
#include<queue>
using std::priority_queue;
using std::vector;
using std::shared_ptr;

class Event;

//	TimeTable, used in a vector to keep track of all the startingtimes and endtimes for the timetable.
struct TimeTable
{
	int trainID;
	Travel travelTo;
	Travel travelFrom;
};

//	Comparing the time for the Priority_queue
class TimeComparison
{
public:
	
	bool operator() (std::shared_ptr<Event> &left, std::shared_ptr<Event> &right)
	{
		return left->getTime() > right->getTime();
	};
};

class Railway
{
public:

	//	Constructor and destructor
	Railway();
	~Railway();

	//	Memberfunctions
	void addTrainStation(Train_Station &ts);
	void printTrainStationNames();
	void readTrainStations();
	void readTrains();
	void printFirstInQueue();
	void scheduleEvent(Event *newEvent);
	int timeToMin(std::string &aString);
	void simMenu();
	void changeInfo();
	void trainMenu();
	void printTrain(std::string trainID);
	void showTimeTable();
	void stationMenu();
	bool printStation(std::string stationName);

	//	Run loop
	void runEvent();
	void run();
	

private:

	Event::TrainStations *vTrainStations;
	Event::EventPrioQ *eventQueue;
	Train_Map *theTrainMap;

	std::vector<std::shared_ptr<Event>> *vEventFinished;
	std::vector<std::shared_ptr<Event>> *vEventIncomplete;
	std::vector<TimeTable> vTimeTable;
	Train_Station *tmpTs;
	
	Information info = LOW;
	int currentTime;
	int interval = 10;
	int endTime = 1439;
	bool startOfSim = true;
};

#endif
