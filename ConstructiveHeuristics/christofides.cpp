#include "city.h"


std::vector<City*> getOdd(std::vector<City*> prim){
	std::vector<City*> odd;
	for(int i=0; i<prim.size(); i++){
		if(prim.at(i)->connections.size()%2 != 0)
			odd.push_back(prim.at(i));
	}
	return odd;
}

std::vector<City*> matching(std::vector<City*> odds, std::vector<City*> prim){
	std::vector<City*> matchGraph;
	for(int i=0; i<odds.size(); i++){
		matchGraph.push_back(copyCity(odds.at(i)));
	}
	City* closest;
	int length, dist = -1;
	std::vector<City*>::iterator tmp, first;
	while (!odds.empty()) {
		first = odds.begin();
		std::vector<City*>::iterator it = odds.begin() + 1;
		std::vector<City*>::iterator end = odds.end();

		length = INT_MAX;
		for (; it != end; ++it) {
			dist = (*first)->distance[(*it)->id];
			if(dist < length){
				length = dist;
				closest = *it;
				tmp = it;
			}
		}
		matchGraph.push_back(copyCity(getCityById((*first)->id, prim)));
		odds.erase(tmp);
		odds.erase(first);
	}
	return matchGraph;
}

std::vector<City*> combineGraphs(std::vector<City*> matchingGraph, std::vector<City*> prim){
	for(int i=0; i<matchingGraph.size(); i++){
		std::vector<std::pair<int, int> > connections = matchingGraph.at(i)->connections;
		int index = findPrimIndex(matchingGraph.at(i)->id, prim);
		if (index >= 0){
			for(int j=0; j<connections.size(); j++){
				City* city = copyCity(getCityById(connections.at(j).first, prim));
				prim.at(index)->distance[city->id] = connections.at(j).second;
			}
		}
	}
	return prim;
}

bool alreadyInRoute(std::vector<int> route, int id){
	for(int i=0; i<route.size(); i++)
		if(route.at(i) == id)
			return true;
	return false;
}

std::pair<std::vector<int>, int> createHamiltonianCycle(std::vector<City*> graph){
	int cost = 0;
	std::vector<int> route;
	City* start = graph.at(0);
	route.push_back(start->id);

	while(route.size() != graph.size()){
		std::map<int, int>::iterator it;
		int dist = INT_MAX;
		int candidate = -1;
		for(it = start->distance.begin(); it != start->distance.end(); it++){
			if(it->second < dist && !alreadyInRoute(route, it->first)){
				candidate = it->first;
				dist = it->second;
			}
		}
		if(candidate != -1){
			route.push_back(candidate);
			cost += dist;
			start = getCityById(candidate, graph);
		}
	}
	int firstCity = route[0];
	int lastCity = route[route.size()-1];
	for (int i = 0; i<graph.size(); i++){
		if (graph[i]->id == firstCity){
			cost += graph[i]->distance[lastCity];
			break;
		}
	}
	route.push_back(lastCity);
	return std::pair<std::vector<int>, int>(route, cost);

}

std::pair<std::vector<int>, int> christofides(std::vector<City*> cities){
	std::vector<City*> prim = primMST(cities);
	std::vector<City*> odd = getOdd(prim);
	std::vector<City*> matchingGraph = matching(odd, prim);
	std::vector<City*> combinedGraphs = combineGraphs(matchingGraph, prim);
	std::pair<std::vector<int>, int> cycle = createHamiltonianCycle(combinedGraphs);
	return cycle;
}