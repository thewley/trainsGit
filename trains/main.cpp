//	Jonathan Bengtsson
//	Projekt Trains V1.0
//	main

#include"train.h"
#include"Train_Map.h"
#include"Train_Station.h"
#include"memstat.hpp"
#include"railway.h"

int main()
{
	//Train t1;
	//t1.add(*new Open_Wagon(1, 10, 12));
	//t1.add(*new Diesel_Locomotive(2, 1.4, 150));
	//t1.print();

	////Train t2;
	////t2.add(*new Open_Wagon(1, 10, 12));
	////t2.add(*new Diesel_Locomotive(2, 1.4, 150));
	////t2.print();
	//
	//Train_Map tm;
	//tm.print();
	//int dist = tm.findDistance("Dunedin", "GrandCentral");
	//std::cout << "Distance from Grand to Dun: " << dist << std::endl;

	//Train_Station ts, ts2;
	//ts.setStationName("LINKOPING");
	//ts.addFordon(*new Open_Wagon(3, 10, 12));
	//ts.addFordon(*new Diesel_Locomotive(4, 10, 120));
	//ts.addFordon(*new Sit_Wagon(5, 1, 100));

	//ts2.setStationName("STHLM");
	//ts2.addFordon(*new Open_Wagon(3, 10, 12));
	//ts2.addFordon(*new Diesel_Locomotive(4, 10, 120));
	//ts2.addFordon(*new Sit_Wagon(5, 1, 100));
	////ts.addToMap(0, *new Open_Wagon(7, 10, 540));
	////ts.addToMap(0, *new Open_Wagon(6, 0, 10));
	////ts.printMap();
	//ts.print();
	//ts.addTrain(t1);
	//ts.print();
	
	std::cout << "*******************************************" << std::endl << std::endl;

	Railway rw;
	
	rw.readTrainStations();
	rw.print();
	rw.readTrains();
	rw.printTT();
	std::cout << "*************************************************" << std::endl;
	rw.printTT();

	std::cout << "*******************************************" << std::endl << std::endl;
	std::cin.get();
	std::cout << "*******************************************" << std::endl << std::endl;
	
	rw.printFirstInQueue();
	rw.printFirstInQueue();

	std::cin.get();
}