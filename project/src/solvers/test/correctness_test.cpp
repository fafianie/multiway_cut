#include "stdafx.h"
#include "graph.h"
#include "planted_instance.h"
#include "mwcsolver.h"
#include "dgf_reader.h"

using namespace std;

int main(int argc, char* argv[]) {
	
	vector<pair<string, int>> instances;
	//instances.push_back({"3__sparse_planar600_3.dgf", 3});
	//instances.push_back({"10__sparse_codeminer_4.dgf", 10});
	instances.push_back({"11__sparse_fvs056_4.dgf", 11});
	//instances.push_back({"16__sparse_planar400_0.dgf", 16});
	//instances.push_back({"19__sparse_clh-10-1_3.dgf", 19});
	//instances.push_back({"19__sparse_hex_3.dgf", 19});
	//instances.push_back({"23__sparse_fvs100_4.dgf", 19});
	
	MWCSolver* solver;
	for (pair<string, int> instance : instances) {
		Graph graph = DGFReader::read("../../resources/test/correctness/", instance.first);	
		
		int** adjacency = new int*[graph.getVertices()];
		for (int i = 0; i < graph.getVertices(); i++) {
			adjacency[i] = new int[graph.getVertices()];
			for (int j = 0; j < graph.getVertices(); j++) {
				if (graph.isOutNeighbor(i, j)){
					adjacency[i][j] = 1;
				} else {
					adjacency[i][j] = 0;
				}
			}
		}
		vector<int> terminals;
		for (auto terminal : graph.getTerminals()) {
			terminals.push_back(terminal);
		}
	
		MWCSolver* solver = new MWCSolver(graph.getVertices(), 
										  graph.getNumberOfTerminals(),
										  terminals,
										  adjacency);
		int solution = solver -> solve();
		if (!(solution == instance.second)) {
			return 1;
		}
	
		delete solver;
		
	}	
	
	return 0;
}