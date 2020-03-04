#include "city.h"

std::pair<std::vector<City*>, bool> readFile(std::string fileName){
	int i = 0;
	bool isEuclidean = false;
	std::vector<City*> cities;
	std::string line;
	std::ifstream tspCoordinatesFile(fileName);
	if (tspCoordinatesFile.is_open()){
		while (getline(tspCoordinatesFile,line)){
			if (i < 6){
				if (i == 4)
					if (line.find("EUC_2D") != std::string::npos) 
						isEuclidean = true;
				i++;
				continue;
			}
			else
				if (line.compare("EOF") != 0 && line.length() > 0)
					cities.push_back(buildCity(line));	
		}
    	tspCoordinatesFile.close();
	}
	else{
		std::cout << "File " << fileName << " does not exist. Aborting execution."<<std::endl;
		exit(EXIT_FAILURE);
	}
	return std::pair<std::vector<City*>, bool>(cities, isEuclidean);
}