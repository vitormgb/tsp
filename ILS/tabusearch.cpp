#include "city.h"

std::pair<std::vector<int>, int> tabusearch(std::vector<int> tour, std::vector<City*> originalCities, int cost){
	std::map<std::vector<int>, int> tabuList;
	std::vector<int> bestTour = tour;
	int bestCost = cost;
	int noImprovement = 0;
	int maxNoImprovement = 1000;
	while (noImprovement < maxNoImprovement){
		std::pair<std::vector<int>, int> result = linkernighan(tour, originalCities, cost, true);
		if (tabuList.find(result.first) == tabuList.end()) {
  			noImprovement++;
		}
		else {
			tour = result.first;
			cost = result.second;
			tabuList.insert(std::pair< std::vector<int> ,int>(result.first, result.second));
			if (result.second < cost){
				bestTour = tour;
				bestCost = result.second;
				noImprovement = 0;
			}
		}
	}
	return std::pair<std::vector<int>, int>(bestTour, bestCost);
}