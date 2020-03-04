#include "city.h"

std::pair<int, int> findNearestCity(std::map<int, int> distance){
	int dist = INT_MAX;
	int city = 0;
	std::map<int, int>::iterator it;
	for (it = distance.begin(); it != distance.end(); it++){
    	if (it->second < dist){
    		city = it->first;
    		dist = it->second;
    	}
	}
	return std::pair<int, int>(city, dist);
}

void updateCityVectorTables(int city, int nextCity, std::vector<City*> *cities){
	for(int i=0; i<cities->size(); i++){
		cities->at(i)->distance[city] = INT_MAX;
		cities->at(i)->distance[nextCity] = INT_MAX;
	}
}


std::pair<int, std::vector<int> > tspNearestNeighbour(std::vector<City*> *cities, int city, int bestSoFar){
	std::vector<City*> citiesCopy = makeCopy(cities);
	int totalRoute = 0;
	std::vector<int> route;
	std::map<int, int> cityDistances;
	route.push_back(city);
	while (route.size() != cities->size()){
		for(int i = 0; i<cities->size(); i++){
			if(cities->at(i)->id == city){
				cityDistances = cities->at(i)->distance;
				break;
			}
		}
		std::pair<int, int> nearestNeighbour = findNearestCity(cityDistances);
		totalRoute += nearestNeighbour.second;
		if (totalRoute >= bestSoFar)
			return std::pair<int, std::vector<int> >(INT_MAX, route);
		updateCityVectorTables(city, nearestNeighbour.first, cities);
		city = nearestNeighbour.first;
		route.push_back(city);
	}
	int firstCity = route[0];
	int lastCity = route[route.size()-1];
	for (int i = 0; i<citiesCopy.size(); i++){
		if (citiesCopy[i]->id == firstCity){
			totalRoute += citiesCopy[i]->distance[lastCity];
			break;
		}
	}
	route.push_back(lastCity);
	return std::pair<int, std::vector<int> >(totalRoute, route);
}

std::pair<std::vector<int>, int> runTspNearestNeighbour(std::vector<City*> cities){
	int bestRouteCost = INT_MAX;
	std::vector<int> bestTour;
	for (int i = 0; i<cities.size(); i++){
		std::vector<City*> citiesCopy = makeCopy(&cities);
		std::pair<int, std::vector<int> > nearestNeighbourHeuristic = tspNearestNeighbour(&citiesCopy, citiesCopy.at(i)->id, bestRouteCost);
		if (bestRouteCost > nearestNeighbourHeuristic.first){
			bestRouteCost = nearestNeighbourHeuristic.first;
			bestTour = nearestNeighbourHeuristic.second;
		}
	}
	return std::pair<std::vector<int>, int>(bestTour, bestRouteCost); 
}