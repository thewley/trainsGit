//	Jonathan Bengtsson
//	Projekt Trains V1.0
//	Headerfil f�r Train

#ifndef TRAIN_H
#define TRAIN_H

#include<vector>
#include"fordon.h"
#include<string>
#include<memory>

enum State { NOT_ASSEMBLED, INCOMPLETE, ASSEMBLED, READY, RUNNING, ARRIVED, FINISHED };
static const char * ENUM_STATE[] = { "Not assembled", "Incomplete", "Assembled", "Ready","Running", "Arrived", "Finished" };

struct Travel
{
	std::string trainstation;
	int time;

};

class Train
{
private:
	std::vector<Fordon*> *vFordon;
	int trainID;
	int trainNumber;
	int delay;
	double maxSpeed;
	double avarageSpeed;
	State state;
	Travel travelFrom;
	Travel travelTo;
	std::string fordonInTrain;

public:

	Train();
	Train(int aTrainID, double aMaxSpeed, Travel aTravelFrom, Travel aTravelTo, std::string aFordonInTrain);
	~Train();


	void add(Fordon &aFordon);
	Travel getTravelFrom() const { return travelFrom; }
	std::string getFordonInTrain() const { return fordonInTrain; }
	void setDelay(int aDelay) { delay += 10; }
	void setState(State aState) { state = aState; }
	void print();

};

#endif