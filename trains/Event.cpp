//	Jonathan Bengtsson
//	Projekt Trains V1.0
//	event.cpp - definitionsfil för event-klassen och arv till event

#include "Event.h"
#include "railway.h"
#include <algorithm>
#include <iterator>
#include <iostream>
#include <fstream>

std::ofstream outFile;
std::vector<int> tmp;

void printOnFile()
{
	outFile.open("incomplete.txt");
	for (auto idx : tmp)
	{
		outFile << idx << std::endl;
	}
	outFile.close();
}


void Not_Assembled::processEvent()
{

	auto it = std::find_if(vTrainStation->begin(), vTrainStation->end(), [&](std::shared_ptr<Train_Station> ts)
	{
		return train->getTravelFrom().trainstation == ts->getTrainStationName();
	});
	
	//std::shared_ptr<Train_Station> ts = *it;

	size_t index = std::distance(vTrainStation->begin(), it);

	//vTrainStation->erase(it);
	//ts->print();
	//vTrainStation->at(index)->print();
	if (vTrainStation->at(index)->assembleTrain(*train))
	{
		//std::cout << "Train assembled! " << std::endl;
		//std::cout << train->getTrainID() << std::endl;
		time += 20;
		//train->print();
		train->setState(ASSEMBLED);
		//vTrainStation->at(index)->print();
		//ts->print();
		//vTrainStation->push_back(ts);

		Event *e = new Assembled(time, train, epQ, vTrainStation);
		epQ->emplace(e);
		
	}
	else
	{

		//std::cout << "Train delayed by 10 minutes!" << std::endl;
		//std::cout << train->getTrainID() << std::endl;
		train->setDelay();
		train->setState(INCOMPLETE);
		/*std::cout << train->getTrainID() << std::endl;*/
		//tmp.push_back(train->getTrainID());
		//printOnFile();
		//vTrainStation->push_back(ts);

		
		//Event *e = new Incomplete(time, train, epQ, vTrainStation);
		//epQ->emplace(e);
		
	}
	
	
	//auto i = std::find_if(ts->)
	//train->add();
		

}

void Not_Assembled::print()
{
	train->print();
}

void Assembled::processEvent()
{
	//std::cout << "ASSEMBLEEEEEEEEEED" << std::endl;
	//std::cout << train->getTrainID() << std::endl;
	train->setState(READY);
	time += 10;
	Event *e = new Ready(time, train, epQ, vTrainStation);
	epQ->emplace(e);
}

void Assembled::print()
{
	train->print();
}

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

void Incomplete::print()
{
	train->print();
}

void Ready::processEvent()
{
	//std::cout << "READYYYYYY" << std::endl;
	//std::cout << train->getTrainID() << std::endl;
	train->setState(RUNNING);
	//std::cout << "TRAIN GOING FROM READY TO RUNNING" << std::endl;
	//std::cout << "ID: " << train->getTrainID()  << " at the time From: "; timeToHandM(train->getTravelFrom().time); std::cout << " To: ";  timeToHandM(train->getTravelTo().time); std::cout << std::endl;
	time = train->getTravelTo().time;
	Event *e = new Running(time,train,epQ,vTrainStation);
	epQ->emplace(e);

}
void Ready::print()
{
	train->print();
}

void Running::processEvent()
{
	//std::cout << "RUNNIN RUNNIN RUNNIN " << std::endl;
	//std::cout << train->getTrainID() << std::endl;
	time = train->getTravelTo().time + train->getDelay() + 20;
	train->setState(ARRIVED);
	printFinishedTrain();
	Event *e = new Arrived(time, train, epQ, vTrainStation);
	epQ->emplace(e);
}

void Running::print()
{
	train->print();
}

void Arrived::processEvent()
{
	//std::cout << "ARRIVED" << std::endl;
	//std::cout << train->getTrainID() << std::endl;
	train->setState(FINISHED);

	auto it = std::find_if(vTrainStation->begin(), vTrainStation->end(), [&](std::shared_ptr<Train_Station> ts)
	{
		return train->getTravelTo().trainstation == ts->getTrainStationName();
	});

	//std::shared_ptr<Train_Station> ts = *it;

	size_t index = std::distance(vTrainStation->begin(), it);
	
	//vTrainStation->at(index)->print();

	if (vTrainStation->at(index)->deassembleTrain(*train));
	{
		
		train->setState(FINISHED);
		//vTrainStation->at(index)->print();
		Event *e = new Finished(time+100000, train);
		epQ->emplace(e);
	}

	


}

void Arrived::print()
{
	train->print();
}

void Running::printFinishedTrain()
{
	std::ofstream outFile("finishedtrains.txt", std::ios::app);
	std::cout << train->getTrainID() << std::endl;
	outFile << std::to_string(train->getTrainID()) << std::endl;

	outFile.close();
}

void Finished::processEvent()
{
	std::cout << "FINISHED TRAIN ******** TOO TOOO " << std::endl;
	std::cout << train->getTrainID() << std::endl;
	
}

void Finished::print()
{
	std::cout << "TRAIN FKIN DONE" << std::endl;
}


