//	Jonathan Bengtsson
//	Projekt Trains V1.0
//	main

#include"train.h"
#include"Train_Map.h"
#include"Train_Station.h"
#include"memstat.hpp"
#include"railway.h"

//	Main
int main()
{

	
	std::cout << "*******************************************" << std::endl << std::endl;

	//	Creating the railway. all files are read in the constructor.
	Railway rw;
	// starting to sim the event.
	rw.run();
	
	std::cout << "*************************************************" << std::endl;


	std::cin.get();
}