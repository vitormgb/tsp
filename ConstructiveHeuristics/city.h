#ifndef city_h
#define city_h
#include <map>
#include <vector>

class City{
	public:
		int id;
		int x, y;
		std::map<int, int> distance;
		std::vector<std::pair<int,int> > connections;
		City* parent;
		City(int id, int x, int y);
		City* buildCity(std::string cityInfo);
		City* getCityById(int, std::vector<City*>);
		int getId();
		int getX();
		int getY();
		bool isVisited();
		City* getParent();
		std::vector<std::pair<int,int> > getConnections();
		std::map<int, int> getMap();

};

#endif