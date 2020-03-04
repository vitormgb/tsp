#include "city.h"

bool alreadyCheckedNeighbor(std::vector<int> *neighbors, int id){
	for(int i = 0; i<neighbors->size(); i++){
		if (neighbors->at(i) == id)
			return true;
	}
	return false;
}

int findClosestToEnd(int end, std::vector<City*> originalCities, std::vector<int> *neighbors, bool tabuSearch=false){
	int distance = INT_MAX;
	int endId = -1;
	City* endCity = NULL;
	for (int i = 0; i<originalCities.size(); i++){
		if(originalCities.at(i)->id == end){
			endCity = originalCities.at(i);
			break;
		}
	}
	if (endCity != NULL){
		std::map<int, int>::iterator it;
		for(it = endCity->distance.begin(); it != endCity->distance.end(); it++){
			if (!tabuSearch){
				if(it->second < distance && !alreadyCheckedNeighbor(neighbors, it->first)){
					distance = it->second;
					endId = it->first;
				}
			}
			else{
				if(it->second < distance){
					distance = it->second;
					endId = it->first;
				}
			}
		}
	}
	return endId;
}

int calculateNewCost(std::vector<int> newTour, std::vector<City*> originalCities){
	int cost = 0;
	for (int i = 0; i<newTour.size() - 1; i++){
		City* c = getCityById(newTour.at(i), originalCities);
		cost += c->distance[newTour.at(i+1)];
	}
	return cost;
}

std::pair<std::vector<int>, int> linkernighan(std::vector<int> tour, std::vector<City*> originalCities, int cost, bool tabuSearch=false){
	std::vector<int> originalTour = tour;
	std::vector<int> checkedNeighbors;
	while(checkedNeighbors.size() < originalTour.size()){
		std::vector<int> newTour;
		tour = originalTour;
		tour.pop_back();
		int closest = findClosestToEnd(tour.at(tour.size()-1), originalCities, &checkedNeighbors);
		int nextToClosest = 0;
		if (closest != -1){
			checkedNeighbors.push_back(closest);
			for (int i = 0; i<tour.size(); i++){
				newTour.push_back(tour.at(i));
				if (tour.at(i) == closest){
					nextToClosest = tour.at(i+1);
					break;
				}
			}
			for (int i = tour.size()-1; tour.at(i) != nextToClosest; i--){
				newTour.push_back(tour.at(i));
			}
			newTour.push_back(nextToClosest);
			newTour.push_back(originalTour.at(0));
			int newCost = calculateNewCost(newTour, originalCities);
			if (newCost < cost && !tabuSearch)
				return std::pair<std::vector<int>, int>(newTour, newCost);
			else{
				originalTour = newTour;
				cost = newCost;
			}
		}
		else{
			return std::pair<std::vector<int>, int>(originalTour, cost);
		}
	}
	return std::pair<std::vector<int>, int>(originalTour, cost);
}