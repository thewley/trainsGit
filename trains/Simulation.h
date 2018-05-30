////	Jonathan Bengtsson
////	Projekt Trains V1.0
////	Simulation.h - Headerfil för Simuleings-klassen
//
//#include "railway.h"
//
//class Simulation
//{
//private:
//	int currentTime;
//	std::priority_queue<std::shared_ptr<Event>, std::vector<std::shared_ptr<Event>>, TimeComparison> *eventQueue;
//
//public:
//
//	Simulation() : currentTime(0) { eventQueue = new std::priority_queue<std::shared_ptr<Event>, std::vector<std::shared_ptr<Event>>, TimeComparison>; }
//	
//	void scheduleEvent(Event *newEvent);
//	void run();
//
//};