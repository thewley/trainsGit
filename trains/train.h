//	Jonathan Bengtsson
//	Projekt Trains V1.0
//	Headerfil för Train

#ifndef TRAIN_H
#define TRAIN_H

#include<vector>
#include"fordon.h"
#include<string>
#include<memory>

//	Enum for the state the train is in.
enum State { NOT_ASSEMBLED, INCOMPLETE, ASSEMBLED, READY, RUNNING, ARRIVED, FINISHED };
static const char * ENUM_STATE[] = { "Not assembled", "Incomplete", "Assembled", "Ready","Running", "Arrived", "Finished" };

//	Enum for what type of information is wanted.
enum Information { LOW, HIGH ,TIMETABLE};
static const char * ENUM_INFORMATION[] = { "low", "high" };

//	Struct Travel, used for where to travel from, and where to travel.
struct Travel
{
	std::string trainstation;
	int time;

};

//	Train class.
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
	//	Constructor
	Train();
	Train(int aTrainID, double aMaxSpeed, Travel aTravelFrom, Travel aTravelTo, std::string aFordonInTrain);
	~Train();


	
	//	Setters and getters.
	Travel getTravelFrom() const { return travelFrom; }
	Travel getTravelTo() const { return travelTo; }
	std::vector<Fordon*> getVFordon() { return *vFordon; }
	std::string getFordonInTrain() const { return fordonInTrain; }
	void setFordonInTrain(std::string _fordonInTrain) { fordonInTrain = _fordonInTrain; }
	int getTrainID() const { return trainID; }
	int getDelay() const { return delay; }
	State getState() const { return state; }
	void setDelay() { delay += 10; }
	void setState(State aState) { state = aState; }

	//	Add and remove Fordon from the vector.
	void add(Fordon *aFordon);
	void clearVFordon() { vFordon->clear(); }

	//	Printfunctions.
	void print(Information info);
	void print();

};

//	Helpfunctions to get the time to hour and min.
void timeToHandM(int time);
std::string toHour(int time);
std::string toMin(int time);

#endif