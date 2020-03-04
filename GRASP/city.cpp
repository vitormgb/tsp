#include "city.h"
#include <map>
#include <sstream>
#include <iterator>
#include <iostream>
#include <vector>
#include <cmath>

City::City(int id, int x, int y){
	this->id = id;
	this->x = x;
	this->y = y;
	this->parent = NULL;
	this->distance.insert(std::pair<int, int>(id, INT_MAX));
}

int City::getId(){
	return id;
}

int City::getX(){
	return x;
}

int City::getY(){
	return y;
}

City* City::getParent(){
	return parent;
}

std::map<int, int> City::getMap(){
	return distance;
}

std::vector<std::pair<int, int> > City::getConnections(){
	return connections;
}

City* buildCity(std::string cityInfo){
	std::istringstream buf(cityInfo);
	std::istream_iterator<std::string> beg(buf), end;
	std::vector<std::string> tokens(beg, end);
	int id = 0, x = 0, y = 0;
	std::stringstream(tokens[0]) >> id;
	std::stringstream(tokens[1]) >> x;
	std::stringstream(tokens[2]) >> y;
	City *city = new City(id, x, y);
	return city;
}

int euclideanDistance(int x1, int x2, int y1, int y2){
	int dx = x1 - x2;
	int dy = y1 - y2;
	return std::round(std::sqrt(dx*dx + dy*dy));
}

int pseudoEuclideanDistance(int x1, int x2, int y1, int y2){
	int xd = x1 - x2;
	int yd = y1 - y2;
	double rij = std::sqrt((xd*xd + yd*yd)/10.0);
	int tij = std::round(rij);
	return tij < rij ? tij + 1 : tij;
}

void generateCityMap(std::vector<City*> *cities, bool isEuclidean, bool applyDisturbance = false){
	for(int i = 0; i<cities->size(); i++){
		for (int j = 0; j<cities->size(); j++){
			if (i != j){
				int dist = 0;
				int disturbance = 0;
				if (isEuclidean)
					dist = euclideanDistance(cities->at(i)->x, cities->at(j)->x, cities->at(i)->y, cities->at(j)->y);
				else
					dist = pseudoEuclideanDistance(cities->at(i)->x, cities->at(j)->x, cities->at(i)->y, cities->at(j)->y);
				if (applyDisturbance){
					int randPair = rand()%10;
					if (randPair%2 == 0)
						randPair = 1;
					else
						randPair = -1;
					disturbance = randPair*(rand() % (( dist + 1 )));
				}
				cities->at(i)->distance.insert(std::pair<int, int>(cities->at(j)->id, abs(dist + disturbance)));
			}
		}
	}
}

std::vector<City*> makeCopy(std::vector<City*> *cities){
	std::vector<City*> citiesCopy;
	for(int i = 0; i<cities->size(); i++){
		City *nCity = new City(cities->at(i)->id, cities->at(i)->x, cities->at(i)->y);
		nCity->distance = cities->at(i)->distance;
		citiesCopy.push_back(nCity);
	}
	return citiesCopy;
}

City* copyCity(City* city){
	City *nCity = new City(city->id, city->x, city->y);
	nCity->distance = city->distance;
	nCity->connections = city->connections;
	nCity->parent = city->parent;
	return nCity;
}

City* getCityById(int id, std::vector<City*> cities){
	for (int i=0; i<cities.size(); i++){
		if (cities.at(i)->id == id)
			return cities.at(i);
	}
	return NULL;
}

std::vector<City*> createCitiesById(std::vector<int> ids, std::vector<City*> cities){
	std::vector<City*> newcities;
	for (int i = 0; i<ids.size(); i++){
		City* city = getCityById(ids.at(i), cities);
		newcities.push_back(city);
	}
	return newcities;
}