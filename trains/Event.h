//	Jonathan Bengtsson
//	Projekt Trains V1.0
//	event.h - Headerfil för event-klassen och arv till event

#ifndef EVENT_H
#define EVENT_H

#include "Train_Station.h"
//#include "railway.h"
#include "Train_Map.h"
#include <queue>
#include <fstream>

using std::priority_queue;
using std::vector;
using std::shared_ptr;



class Railway;
class TimeComparison;


//	Class event, abstract class.
class Event
{
public:
	//	Typedef
	typedef vector<shared_ptr<Event>> Events;
	typedef priority_queue<shared_ptr<Event>, Events, TimeComparison> EventPrioQ;
	typedef vector<shared_ptr<Train_Station>> TrainStations;

	//	Constructor
	Event(int t) : time(t) {}

	//	Memberfunctions
	int getTime() const { return time; }
	virtual ~Event() {}
	virtual void processEvent() = 0;
	virtual void print(Information info) =0;
	virtual State getState() const =0;
	virtual void printOnFile(Train *train, State state);

protected:
	int time;
};

//	Not_Assembled, inheritance from Event.
class Not_Assembled : public Event
{
protected:
	std::shared_ptr<Train> train;
	EventPrioQ *epQ;
	TrainStations *vTrainStation;

public:
	Not_Assembled(int t, Train *aTrain, EventPrioQ *&_epQ, TrainStations *&_vTrainStation) 
		:Event::Event(t), train(aTrain), epQ(_epQ), vTrainStation(_vTrainStation) {}
	
	State getState() const { return train->getState(); }

	// Inherited via Event
	virtual void processEvent() override;
	virtual void print(Information info) override;

};

//	Assembled, inheritance from Event.
class Assembled : public Event
{
protected:
	std::shared_ptr<Train> train;
	EventPrioQ *epQ;
	TrainStations *vTrainStation;
public:
	Assembled(int t, shared_ptr<Train> aTrain, EventPrioQ *&_epQ, TrainStations *&_vTrainStation) 
		:Event::Event(t), train(aTrain), epQ(_epQ), vTrainStation(_vTrainStation){}


	virtual State getState() const { return train->getState(); }
	// Inherited via Event
	virtual void processEvent() override;
	virtual void print(Information info) override;
};

//	Incomplete, inheritance from Event.
class Incomplete : public Event
{
protected:
	std::shared_ptr<Train> train;
	EventPrioQ *epQ;
	TrainStations *vTrainStation;
public:
	Incomplete(int t, shared_ptr<Train> aTrain, EventPrioQ *&_epQ, TrainStations *&_vTrainStation)
		:Event::Event(t), train(aTrain), epQ(_epQ), vTrainStation(_vTrainStation) {}

	virtual State getState() const { return train->getState(); }
	// Inherited via Event
	virtual void processEvent() override;
	virtual void print(Information info) override;

};

//	Ready, inheritance from Event.
class Ready : public Event
{
protected:
	std::shared_ptr<Train> train;
	EventPrioQ *epQ;
	TrainStations *vTrainStation;
public:
	Ready(int t, shared_ptr<Train> aTrain, EventPrioQ *&_epQ, TrainStations *&_vTrainStation)
		:Event::Event(t), train(aTrain), epQ(_epQ), vTrainStation(_vTrainStation) {}

	virtual State getState() const { return train->getState(); }
	// Inherited via Event
	virtual void processEvent() override;
	virtual void print(Information info) override;

};

//	Running, inheritance from Event.
class Running : public Event
{
protected:
	std::shared_ptr<Train> train;
	EventPrioQ *epQ;
	TrainStations *vTrainStation;
	//For higher grade
	//Train_Map tm;
public:
	Running(int t, shared_ptr<Train> aTrain, EventPrioQ *&_epQ, TrainStations *&_vTrainStations)
		:Event::Event(t), train(aTrain), epQ(_epQ), vTrainStation(_vTrainStations) {}

	virtual State getState() const { return train->getState(); }
	void printFinishedTrain();
	// Inherited via Event
	virtual void processEvent() override;
	virtual void print(Information info) override;
	
};

//	Arrived, inheritance from Event.
class Arrived : public Event
{
protected:
	std::shared_ptr<Train> train;
	EventPrioQ *epQ;
	TrainStations *vTrainStation;

public:
	Arrived(int t, shared_ptr<Train> aTrain, EventPrioQ *&_epQ, TrainStations *&_vTrainStation)
		:Event::Event(t), train(aTrain), epQ(_epQ), vTrainStation(_vTrainStation) {}

	virtual State getState() const { return train->getState(); }
	// Inherited via Event
	virtual void processEvent() override;
	virtual void print(Information info) override;
	

};

//	Finished, inheritance from Event.
class Finished : public Event
{
protected:
	std::shared_ptr<Train> train;

public:
	Finished(int t, shared_ptr<Train> aTrain)
		:Event::Event(t), train(aTrain){}

	virtual State getState() const { return train->getState(); }
	// Inherited via Event
	virtual void processEvent() override;
	virtual void print(Information info) override { train->print(info); };

};

//	Helpfunction to print the time table.
void printTT(std::shared_ptr<Train> train);

#endif