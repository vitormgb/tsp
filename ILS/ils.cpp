int generateIntRandom(int lim){
	std::random_device rd{};    
	std::mt19937 engine{rd()};
	std::uniform_int_distribution<int> idist(0, lim-1);
	return idist(engine);
}

int findIndex(std::vector<int> tour, int id){
	for(int i=0; i<tour.size(); i++){
		if (tour.at(i) == id)
			return i;
	}
	return -1;
}

std::pair<std::vector<int>, int> ils(std::vector<City*> cities, std::vector<int> tour, int cost){
	std::vector<int> bestTour = tour;
	int numberOfCities = tour.size();
	int maxNotImproving = 300;
	int perturbation = 1;
	int i = 0;
	while (i < maxNotImproving){
		int k = 0;
		std::vector<int> indexOfcitiesToChange;
		while (k < perturbation){
			int rand = generateIntRandom(numberOfCities);
			indexOfcitiesToChange.push_back(rand);
			k++;
		}
		k = 0;
		while(k < indexOfcitiesToChange.size()){
			int indexToChange = generateIntRandom(numberOfCities);
			if(indexToChange != indexOfcitiesToChange.at(k)){
				int fCity = tour.at(indexToChange);
				int sCity = tour.at(indexOfcitiesToChange.at(k));
				tour.at(indexToChange) = sCity;
				tour.at(indexOfcitiesToChange.at(k)) = fCity;
				k++;
			}
		}
		int newCost = calculateNewCost(tour, cities);
		if(newCost > 0 && newCost < cost){
			cost = newCost;
			bestTour = tour;
			perturbation = 1;
			i = 0;
		}
		else{
			i++;
			perturbation++;
		}
	}
	return std::pair<std::vector<int>, int>(tour, cost);
}