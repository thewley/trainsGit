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

	Railway();
	~Railway();
	void addTrainStation(Train_Station &ts);
	void print();
	void readTrainStations();
	void readTrains();
	void printFirstInQueue();
	void scheduleEvent(Event *newEvent);
	int timeToMin(std::string &aString);
	void doMenuTwo();

	void runEvent();
	void run();

private:

	Event::TrainStations *vTrainStations;
	Event::EventPrioQ *eventQueue;
	Train_Map *theTrainMap;

	std::vector<Event> *vEvent;
	// std::priority_queue<Event*, std::vector<Event*>, TimeComparison> *eventQueue;
	Train_Station *tmpTs;

	int currentTime;
	int interval = 10;
	
};


//bool operator<(const std::shared_ptr<Event> &lhs, const std::shared_ptr<Event> &rhs)
//{
//	return lhs->getTime() < rhs->getTime();
//};
#endif
