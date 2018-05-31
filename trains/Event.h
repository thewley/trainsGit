//	Jonathan Bengtsson
//	Projekt Trains V1.0
//	event.h - Headerfil för event-klassen och arv till event

#ifndef EVENT_H
#define EVENT_H

#include "Train_Station.h"
//#include "railway.h"
#include "Train_Map.h"
#include <queue>

using std::priority_queue;
using std::vector;
using std::shared_ptr;



class Railway;
class TimeComparison;



class Event
{
public:
	typedef vector<shared_ptr<Event>> Events;
	typedef priority_queue<shared_ptr<Event>, Events, TimeComparison> EventPrioQ;
	typedef vector<shared_ptr<Train_Station>> TrainStations;

	Event(int t) : time(t) {}

	virtual ~Event() {}
	virtual void processEvent() = 0;
	int getTime() const { return time; }
	virtual void print() =0;



protected:
	int time;
};

class Not_Assembled : public Event
{
protected:
	std::shared_ptr<Train> train;
	EventPrioQ *epQ;
	TrainStations *vTrainStation;

public:
	Not_Assembled(int t, Train *aTrain, EventPrioQ *&_epQ, TrainStations *&_vTrainStation) 
		:Event::Event(t), train(aTrain), epQ(_epQ), vTrainStation(_vTrainStation) {}
	
	// Inherited via Event
	virtual void processEvent() override;
	virtual void print() override;
};


class Assembled : public Event
{
protected:
	std::shared_ptr<Train> train;
	EventPrioQ *epQ;
	TrainStations *vTrainStation;
public:
	Assembled(int t, shared_ptr<Train> aTrain, EventPrioQ *&_epQ, TrainStations *&_vTrainStation) 
		:Event::Event(t), train(aTrain), epQ(_epQ), vTrainStation(_vTrainStation){}

	// Inherited via Event
	virtual void processEvent() override;
	virtual void print() override;
};

class Incomplete : public Event
{
protected:
	std::shared_ptr<Train> train;
	EventPrioQ *epQ;
	TrainStations *vTrainStation;
public:
	Incomplete(int t, shared_ptr<Train> aTrain, EventPrioQ *&_epQ, TrainStations *&_vTrainStation)
		:Event::Event(t), train(aTrain), epQ(_epQ), vTrainStation(_vTrainStation) {}


	// Inherited via Event
	virtual void processEvent() override;
	virtual void print() override;

};

class Ready : public Event
{
protected:
	std::shared_ptr<Train> train;
	EventPrioQ *epQ;
	TrainStations *vTrainStation;
public:
	Ready(int t, shared_ptr<Train> aTrain, EventPrioQ *&_epQ, TrainStations *&_vTrainStation)
		:Event::Event(t), train(aTrain), epQ(_epQ), vTrainStation(_vTrainStation) {}


	// Inherited via Event
	virtual void processEvent() override;
	virtual void print() override;

};

class Running : public Event
{
protected:
	std::shared_ptr<Train> train;
	EventPrioQ *epQ;
	TrainStations *vTrainStation;
	//Train_Map tm;
public:
	Running(int t, shared_ptr<Train> aTrain, EventPrioQ *&_epQ, TrainStations *&_vTrainStations)
		:Event::Event(t), train(aTrain), epQ(_epQ), vTrainStation(_vTrainStations) {}

	// Inherited via Event
	virtual void processEvent() override;
	virtual void print() override;
	void printFinishedTrain();
};

class Arrived : public Event
{
protected:
	std::shared_ptr<Train> train;
	EventPrioQ *epQ;
	TrainStations *vTrainStation;

public:
	Arrived(int t, shared_ptr<Train> aTrain, EventPrioQ *&_epQ, TrainStations *&_vTrainStation)
		:Event::Event(t), train(aTrain), epQ(_epQ), vTrainStation(_vTrainStation) {}


	// Inherited via Event
	virtual void processEvent() override;
	virtual void print() override;
	

};

class Finished : public Event
{
protected:
	std::shared_ptr<Train> train;

public:
	Finished(int t, shared_ptr<Train> aTrain)
		:Event::Event(t), train(aTrain){}


	// Inherited via Event
	virtual void processEvent() override;
	virtual void print() override;

};

#endif