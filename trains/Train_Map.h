//	Jonathan Bengtsson
//	Projekt Trains V1.0
//	Headerfil för Train_Map-klassen

#ifndef TRAIN_MAP_H
#define TRAIN_MAP_H

#include<vector>
#include<string>
#include<memory>
#include<iostream>


struct Distance
{
	std::string stationOne;
	std::string stationTwo;
	int distance;
};

class Train_Map
{
private:
	std::vector<Distance> *vDistance;

public:

	Train_Map();
	~Train_Map() { vDistance->clear(); delete vDistance; std::cout << "~Train_Map" << std::endl; }

	void print();
	int findDistance(std::string aDistanceFrom, std::string aDistanceTo);

};

#endif
