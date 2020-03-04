#include <fstream>
#include <ctime>
#include <climits>
#include "city.cpp" // graph file construction
#include "readFile.cpp" // input file reader
//#include "nearestNeighbour.cpp" // nearest neighbour heuristic for tsp
#include "prim.cpp" // prim mst algorithm 
#include "christofides.cpp" // christofides algorithm
#include "linkernighan.cpp" // linkernighan algorithm for tsp improvement
//#include "tabusearch.cpp" // tabu search
#include "grasp.cpp" //grasp
#include "verifySolution.cpp" // answer validator

int main(int argc, char *argv[]){
	if (argc > 1){
		std::clock_t begin = clock();
		std::pair<std::vector<City*>, bool> inputFile = readFile(argv[1]);
		generateCityMap(&inputFile.first, inputFile.second);
		std::pair<std::vector<int>, int> heuristic = christofides(inputFile.first);
		std::vector<int> solution = heuristic.first;
		int cost = heuristic.second;
		heuristic = grasp(inputFile.first, solution, cost, inputFile.second);
		std::clock_t end = clock();
 		double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
 		bool validSolution = verifySolution(heuristic.first, inputFile.first.size());
 		if (validSolution){
 			std::cout<<"Map: "<<argv[1]<<std::endl;
	 		if (inputFile.second)
	 			std::cout<<"Type: Euclidean Distance"<<std::endl;
	 		else
	 			std::cout<<"Type: Pseudo-Euclidean Distance"<<std::endl;
			std::cout<<"TSP Cost: "<<heuristic.second<<std::endl<<"Time Elapsed: "<<elapsed_secs<<"s"<<std::endl;
		}
		else
			std::cout<<"Invalid Solution."<<std::endl;
	}
	else
		std::cout<<"Argument not found: 'file.tsp'"<<std::endl;
	return 0;
}