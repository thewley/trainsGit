//	Jonathan Bengtsson
//	Projekt Trains V1.0
//	Headerfil för klassen railway

#ifndef RAILWAY_H
#define RAILWAY_H

#include"Train_Station.h"
#include"Event.h"
#include<memory>
#include<queue>


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
private:
	std::vector<std::shared_ptr<Train_Station>> *vTrainStation;
	std::vector<Event> *vEvent;
	std::priority_queue<std::shared_ptr<Event>, std::vector<std::shared_ptr<Event>>, TimeComparison> *eventQueue;
	// std::priority_queue<Event*, std::vector<Event*>, TimeComparison> *eventQueue;
	Train_Station *tmpTs;
	int currentTime;

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
	void run();
};


//bool operator<(const std::shared_ptr<Event> &lhs, const std::shared_ptr<Event> &rhs)
//{
//	return lhs->getTime() < rhs->getTime();
//};
#endif
