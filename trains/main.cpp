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

	
	std::cout << "*******************************************" << std::endl << std::endl;

	Railway rw;
	
	rw.run();

	
	std::cout << "*************************************************" << std::endl;


	std::cin.get();
}