//	Jonathan Bengtsson
//	Projekt Trains V1.0
//	event.cpp - definitionsfil för event-klassen och arv till event

#include "Event.h"
#include "railway.h"
#include <algorithm>
#include <iterator>
#include <iostream>
#include <fstream>
#include <iomanip>
//	All events print on file.

//	Processing the Not_Assembled event, Finds the correct station and tries to assemble the train, if it works the train is set as assembled, otherwise it will be incomplete.
void Not_Assembled::processEvent()
{

	auto it = std::find_if(vTrainStation->begin(), vTrainStation->end(), [&](std::shared_ptr<Train_Station> ts)
	{
		return train->getTravelFrom().trainstation == ts->getTrainStationName();
	});
	
	size_t index = std::distance(vTrainStation->begin(), it);

	if (vTrainStation->at(index)->assembleTrain(*train))
	{

		printOnFile(train.get(), ASSEMBLED);

		time += 20;
		train->setState(ASSEMBLED);
		
		Event *e = new Assembled(time, train, epQ, vTrainStation);
		epQ->emplace(e);
	}
	else
	{
		printOnFile(train.get(), INCOMPLETE);
		train->setDelay();
		train->setState(INCOMPLETE);

		Event *e = new Incomplete(time+3000, train, epQ, vTrainStation);
		epQ->emplace(e);
		
	}
}

//	Print for the not_assembled event
void Not_Assembled::print(Information info)
{
	if (info == TIMETABLE)
		printTT(train);
	else
	{
		train->print(info);
		std::cout << "is now assembled " << std::endl << std::endl;
	}
	

}

//	Processing the Assembled event, making the train ready and putting it back in the queue as a ready event.
void Assembled::processEvent()
{
	printOnFile(train.get(), READY);
	train->setState(READY);
	time += 10;
	Event *e = new Ready(time, train, epQ, vTrainStation);
	epQ->emplace(e);
}

//	Printing the assembled event.
void Assembled::print(Information info)
{
	if (info == TIMETABLE)
		printTT(train);
	else
	{
		train->print(info);
		std::cout << "is now ready" << std::endl << std::endl;
	}
}

//	För högre betyg
void Incomplete::processEvent()
{
	//std::cout << "INCOMPLETE" << std::endl;
	//std::cout << train->getTrainID() << std::endl;
	//auto it = std::find_if(vTrainStation->begin(), vTrainStation->end(), [&](const std::shared_ptr<Train_Station> ts)
	//{
	//	return train->getTravelFrom().trainstation == ts->getTrainStationName();
	//});
	//std::shared_ptr<Train_Station> ts = *it;

	//vTrainStation->erase(it);

	//if (ts->assembleTrain(*train))
	//{
	//	std::cout << "Train assembled! " << std::endl;
	//	time += 20;
	//	train->print();
	//	train->setState(ASSEMBLED);
	//	vTrainStation->push_back(ts);
	//	Event *e = new Assembled(time, train, epQ,vTrainStation);
	//	epQ->emplace(e);

	//}
	//else
	//{
	//	std::cout << "Train delayed by 10 minutes!" << std::endl;
	//	train->setDelay();
	//	train->setState(INCOMPLETE);
	//	vTrainStation->push_back(ts);
	//	Event *e = new Incomplete(time, train, epQ, vTrainStation);
	//	epQ->emplace(e);
	//}

	
}

//	Printing the incomplete event.
void Incomplete::print(Information info)
{
	if (info == TIMETABLE)
		printTT(train);
	else
	{
		train->print(info);
		std::cout << "is now incomplete" << std::endl << std::endl;
	}	
}

//	Processing a ready event, makes so it goes into running and pusing back a new running event.
void Ready::processEvent()
{
	printOnFile(train.get(), RUNNING);
	train->setState(RUNNING);
	time = train->getTravelTo().time;
	Event *e = new Running(time,train,epQ,vTrainStation);
	epQ->emplace(e);

}

//	Printing the ready event.
void Ready::print(Information info)
{
	if (info == TIMETABLE)
		printTT(train);
	else
	{
		train->print(info);
		std::cout << "is now running" << std::endl << std::endl;
	}
}

//	Processing the running event, making it to the state Arrived and pushing a new arrived event to the queue.
void Running::processEvent()
{
	printOnFile(train.get(), ARRIVED);
	time = train->getTravelTo().time + train->getDelay() + 20;
	train->setState(ARRIVED);
	Event *e = new Arrived(time, train, epQ, vTrainStation);
	epQ->emplace(e);
}

//	Printing the Running event
void Running::print(Information info)
{
	if (info == TIMETABLE)
		printTT(train);
	else
	{
		train->print(info);
		std::cout << "has now arrived" << std::endl << std::endl;
	}	
}

//	Processing the Arrived event, finding the station it reached, and deassemble the train there, also puts the train in the new station.
void Arrived::processEvent()
{
	printOnFile(train.get(), FINISHED);
	train->setState(FINISHED);
	//	Getting the station the train left from and removes the train from that station
	auto itFrom = std::find_if(vTrainStation->begin(), vTrainStation->end(), [&](std::shared_ptr<Train_Station> ts)
	{
		return train->getTravelFrom().trainstation == ts->getTrainStationName();
	});
	size_t indexFrom = std::distance(vTrainStation->begin(), itFrom);
	vTrainStation->at(indexFrom)->removeTrain(train->getTrainID());

	//	Placing the train at the arrival station.
	auto itTo = std::find_if(vTrainStation->begin(), vTrainStation->end(), [&](std::shared_ptr<Train_Station> ts)
	{
		return train->getTravelTo().trainstation == ts->getTrainStationName();
	});
	size_t indexTo = std::distance(vTrainStation->begin(), itTo);
	vTrainStation->at(indexTo)->addTrain(train.get());

	//	Deassemble the train at the arrival station.
	if (vTrainStation->at(indexTo)->deassembleTrain(*train));
	{
		
		train->setState(FINISHED);
		Event *e = new Finished(time+100000, train);
		epQ->emplace(e);
	}

}

//	Printing the Arrived event.
void Arrived::print(Information info)
{
	if (info == TIMETABLE)
		printTT(train);
	else
	{
		train->print(info);
		std::cout << "is now finished" << std::endl << std::endl;
	}	
}

//	Printing all the finnished trains, might remove this.
void Running::printFinishedTrain()
{
	std::cout << train->getTrainID() << std::endl;
}

//	Printing the finished event, (for the future)
void Finished::processEvent()
{
	std::cout << "FINISHED TRAIN ******** TOO TOOO " << std::endl;
	std::cout << train->getTrainID() << std::endl;
	
}


//Help print functions,

//	Printing the time table
void printTT(std::shared_ptr<Train> train)
{
	std::cout << " From: " << train->getTravelFrom().trainstation << "("; timeToHandM(train->getTravelFrom().time); std::cout << ")" << std::endl;
	std::cout << " To: " << train->getTravelTo().trainstation << "("; timeToHandM(train->getTravelTo().time); std::cout << ")" << std::endl << std::endl;
}

//	Printing every step on the trainsim.log
void Event::printOnFile(Train *train, State state)
{
	std::ofstream outFile("trainsim.log", std::ios::app);

	outFile <<std::setw(2) << std::setfill('0') << toHour(time) << ":" << std::setw(2) << std::setfill('0') << toMin(time) << " Train: " << train->getTrainID() << " State: " << ENUM_STATE[train->getState()] << std::endl;
	outFile << "is now " << ENUM_STATE[state] << std::endl;
	outFile.close();
}
