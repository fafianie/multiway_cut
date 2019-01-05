#include "stdafx.h"
#include "graph.h"
#include "planted_instance.h"
#include "mwcsolver.h"

using namespace std;

int main(int argc, char* argv[]) {
	
	for (int repetition = 0; repetition < 1000; repetition++) {
		Graph* graph = new PlantedInstance(100, 7, 5, 300 ,10, 20, 4);
	
		int** adjacency = new int*[100];
		for (int i = 0; i < graph -> getVertices(); i++) {
			adjacency[i] = new int[100];
			for (int j = 0; j < graph -> getVertices(); j++) {
				if (graph -> isOutNeighbor(i, j)){
					adjacency[i][j] = 1;
				} else {
					adjacency[i][j] = 0;
				}
			}
		}
		vector<int> terminals;
		for (auto terminal : graph -> getTerminals()) {
			terminals.push_back(terminal);
		}
	
	
		MWCSolver* solver = new MWCSolver(graph -> getVertices(), 
										  graph -> getNumberOfTerminals(),
										  terminals,
										  adjacency);
		int solution = solver -> solve();
		if (solution == 4) {
			return 1;
		}
	
		delete graph;
	}
	
	
	return 0;
}