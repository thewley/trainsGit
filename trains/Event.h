//	Jonathan Bengtsson
//	Projekt Trains V1.0
//	event.h - Headerfil för event-klassen och arv till event

#ifndef EVENT_H
#define EVENT_H

#include"train.h"


class Event
{
protected:
	int time;

	Train * train;
	int trainId;
	Travel travelFrom;
	Travel travelTo;
	double maxSpeed;
	std::string fordon;

public:

	Event(int t) : time(t) {}

	virtual ~Event() {}

	virtual void processEvent() = 0;
	
	int getTime() const { return time; }

	virtual Travel getTravelFrom() const { return travelFrom; }
	virtual Travel getTravelTo() const { return travelTo; }
	virtual int getTrainId() const { return trainId; }
	virtual int getMaxSpeed() const { return maxSpeed; }
	virtual std::string getFordon() const { return fordon; }

};

class Not_Assembled : public Event
{
protected:
	Train * train;
	int trainId;
	Travel travelFrom;
	Travel travelTo;
	double maxSpeed;
	std::string fordon;
public:
	Not_Assembled(int t, int aTrainId, Travel aTF, Travel aTT, int aMaxSpeed, std::string aFordon) :Event::Event(t), trainId(aTrainId), travelFrom(aTF), travelTo(aTT), maxSpeed(aMaxSpeed), fordon(aFordon) {}
	
	
	// Inherited via Event
	virtual void processEvent() override;

	Travel getTravelFrom() const override { return travelFrom; }
	Travel getTravelTo() const override { return travelTo; }
	int getTrainId() const override { return trainId; }
	int getMaxSpeed() const override { return maxSpeed; }
	std::string getFordon() const override { return fordon; }


};

#endif