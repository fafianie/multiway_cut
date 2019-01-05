#include "stdafx.h"
#include "graph.h"
#include "planted_instance.h"
#include "mwcsolver.h"

using namespace std;

int main(int argc, char* argv[]) {
	
	Graph* graph = new PlantedInstance(100, 7, 5, 300 ,10, 20, 4);
	
	int** adjacency = new int*[];
	for (int i = 0; i < graph -> getVertices(), i++) {
		adjacency[i] = new int[];
		for (int j = 0; j < graph -> getVertices(), j++) {
			if (graph -> isOutNeighbor(i, j)){
				adjacency[i][j] = 1;
			} else {
				adjacency[i][j] = 0;
			}
		}
	}
	
	MWCsolver solver = new MWCSolver(graph -> getVertices(), 
								 graph -> getNumberOfTerminals(), 
								 graph -> getTerminals(),
								 adjacency);
	int solution = solver.solve();
	if (solution > 4) {
		return 1;
	}
	
	delete graph;
	
	return 0;
}