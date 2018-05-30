//	Jonathan Bengtsson
//	Projekt Trains V1.0
//	event.h - Headerfil för event-klassen och arv till event

#ifndef EVENT_H
#define EVENT_H

#include "Train_Station.h"
//#include "railway.h"
#include <queue>

class TimeComparison;

class Event
{
protected:
	int time;

	std::shared_ptr<Train> train;

public:

	Event(int t) : time(t) {}

	virtual ~Event() {}

	virtual void processEvent(std::vector<std::shared_ptr<Train_Station>> &vTrainStation) = 0;
	
	int getTime() const { return time; }

	virtual void print();

};

class Not_Assembled : public Event
{
protected:
	std::shared_ptr<Train> train;

public:
	Not_Assembled(int t, Train *aTrain) :Event::Event(t), train(aTrain) {}
	
	// Inherited via Event
	virtual void processEvent(std::vector<std::shared_ptr<Train_Station>> &vTrainStation) override;
};


class Assembled : public Event
{
protected:
	std::shared_ptr<Train> train;

public:
	Assembled(int t, std::shared_ptr<Train> aTrain) :Event::Event(t), train(aTrain) {}

	// Inherited via Event
	virtual void processEvent(std::vector<std::shared_ptr<Train_Station>> &vTrainStation) override;
};

#endif