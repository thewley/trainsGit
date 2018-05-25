//	Jonathan Bengtsson
//	Projekt Trains V1.0
//	Headerfil för Train

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
	double avarageSpeed;
	State state;
	Travel travelFrom;
	Travel travelTo;

public:

	Train();
	~Train();


	void add(Fordon &aFordon);

	void print();

};

#endif