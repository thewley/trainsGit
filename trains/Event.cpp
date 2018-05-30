//	Jonathan Bengtsson
//	Projekt Trains V1.0
//	event.cpp - definitionsfil för event-klassen och arv till event

#include "Event.h"
#include<algorithm>
#include<iterator>

void Not_Assembled::processEvent(std::vector<std::shared_ptr<Train_Station>> &vTrainStation)
{
	auto it = std::find_if(vTrainStation.begin(), vTrainStation.end(), [&](const std::shared_ptr<Train_Station> ts)
	{
		return train->getTravelFrom().trainstation == ts->getTrainStationName();
	});
	std::shared_ptr<Train_Station> ts = *it;

	vTrainStation.erase(it);

	if (ts->assembleTrain(*train))
	{
		std::cout << "Train assembled! " << std::endl;
		time += 20;
		train->print();
		train->setState(ASSEMBLED);
		//Event *e = new Assembled(time, train);
	}
	else
	{
		std::cout << "Train delayed by 10 minutes!" << std::endl;
	}

	vTrainStation.push_back(ts);
	//auto i = std::find_if(ts->)
	//train->add();
		

}



void Event::print()
{
	train->print();
}

void Assembled::processEvent(std::vector<std::shared_ptr<Train_Station>>& vTrainStation)
{
}
