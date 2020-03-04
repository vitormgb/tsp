bool verifySolution(std::vector<int> solution, int size){
	bool firstCity = false;
	std::vector<int> verifier(size, 0);
	for (int i = 0; i<solution.size(); i++){
		verifier.at(solution.at(i) - 1) += 1; 
	}
	for (int i = 0; i<verifier.size(); i++){
		if(verifier.at(i) == 0){ // found not visited city
			std::cout<<"City "<<i+1<<" not visited."<<std::endl;
			return false;
		}
		else if (verifier.at(i) == 2){ // found where the tour begun
			if (!firstCity){
				firstCity = true; // found it once
			}
			else{
				std::cout<<"City "<<i+1<<" found twice."<<std::endl;
				return false; // found it twice, thus repeated city
			}
		}
	}
	return firstCity; // true if found where the tour begun, if all cities were visited and if the beginning was found only once
}