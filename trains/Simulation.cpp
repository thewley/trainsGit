//#include "Simulation.h"
//
//void Simulation::scheduleEvent(Event * newEvent)
//{
//	eventQueue->emplace(newEvent);
//}
//void Simulation::run()
//{
//	while (!eventQueue->empty())
//	{
//		std::shared_ptr<Event> ev = eventQueue->top();
//		eventQueue->pop();
//		currentTime = ev->getTime();
//		ev->processEvent(*vTrainStation);
//	}
//}
//
