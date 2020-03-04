#include "city.h"
float alpha = 0.7; //alpha value for grasp

int getRealCost(std::vector<City*> cities, std::vector<int> solution){
	int cost = 0;
	for (int i = 0; i<solution.size() - 1; i++){
		City* city = getCityById(solution.at(i), cities);
		int nextCity = solution.at(i+1);
		cost += city->distance[nextCity];
	}
	return cost;
}

std::pair<std::vector<int>, int> grasp(std::vector<City*> cities, std::vector<int> solution, int cost, bool isEuclidean){
	int iterations = 0;
	int maxIterations = 100;
	int min, max;
	std::vector<City*> copy = makeCopy(&cities);
	std::vector<std::pair<std::vector<int>, int> > LRC;
	LRC.push_back(std::pair<std::vector<int>, int>(solution, cost));

	std::pair<std::vector<int>, int> lk = linkernighan(solution, cities, cost);
	if (lk.second < cost){
		max = cost;
		min = lk.second;
	}
	else{
		max = lk.second;
		min = cost;
	}

	while (iterations < maxIterations){
		if (LRC.size() > 1){
			int random = rand()%LRC.size();
			std::cout<<random;
			copy = createCitiesById(LRC[random].first, cities);
		}
		generateCityMap(&copy, isEuclidean, true);
		std::pair<std::vector<int>, int> heuristic = christofides(copy);
		heuristic = linkernighan(solution, cities, cost);
		int realCost = getRealCost(cities, heuristic.first);
		if (realCost <= (min + alpha*(max - min))){
			LRC.clear();
			LRC.push_back(std::pair<std::vector<int>, int>(heuristic.first, realCost));
		}
		iterations++;
		
	}
	int minCost = INT_MAX;
	for (int i = 0; i<LRC.size(); i++){
		if (LRC.at(i).second < minCost){
			minCost = LRC.at(i).second;
			solution = LRC.at(i).first;
		}
	}
	return std::pair<std::vector<int>, int>(solution, minCost);
}