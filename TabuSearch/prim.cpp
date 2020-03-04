#include "city.h"

std::vector<City*> primMST(std::vector<City*> cities){
	std::vector<City*> prim;
	City* start = copyCity(cities.at(0));
	prim.push_back(start);
	while(prim.size() != cities.size()){
		City* next = NULL;
		City* parent = NULL;
		int dist = INT_MAX;
		std::map<int, int>::iterator iter;
		for(int i=0; i<prim.size(); i++){
			for(iter = prim.at(i)->distance.begin(); iter != prim.at(i)->distance.end(); iter++){
				if(iter->second < dist && getCityById(iter->first, prim) == NULL){
					next = copyCity(getCityById(iter->first, cities));
					parent = prim.at(i);
					dist = iter->second;
				}
			}
		}
		if(next != NULL && parent != NULL){
			prim.push_back(next);
			parent->connections.push_back(std::pair<int,int>(next->id,dist));
			next->connections.push_back(std::pair<int,int>(parent->id,dist));
			next->parent = parent;
		}
	}
	return prim;
}

int findPrimIndex(int id, std::vector<City*> prim){
	for(int i=0; i<prim.size(); i++){
		if(prim.at(i)->id == id)
			return i;
	}
	return -1;
}