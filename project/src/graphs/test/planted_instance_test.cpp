#include "stdafx.h"
#include "graph.h"
#include "multiway_cut_solver.h"
#include "planted_instance.h"

using namespace std;

int main(int argc, char* argv[]) {
	int vertices, clusters, terminals, edges, hubSize, hubEdges, budget;
						//  vertices	clusters	terminals	edges		hubSize		hubEdges	budget		clust-size 	min edges	max edges
	vector<int> instance1{	50			,4			,3			,150		,5			,5			,3	}; 	//	11			40			384
	vector<int> instance2{	100			,5			,4			,500		,7			,7			,4	};  //	18			85			1189
	vector<int> instance3{	150			,6			,5			,1000		,9			,9			,5	};  //	23			132			2314
	vector<int> instance4{	200			,7			,6			,1750		,11			,11			,6	};  //	27			182			3742
	
	vector<vector<int>> instances{instance1, instance2, instance3, instance4};
	
	for (vector<int> instance : instances) {
		int vertices = instance[0];
		int clusters = instance[1];
		int terminals = instance[2];
		int edges = instance[3];
		int hubSize = instance[4];
		int hubEdges = instance[5];
		int budget = instance[6];
		PlantedInstance graph(vertices, clusters, terminals, edges, hubSize, hubEdges, budget);
		MultiwayCutSolver solver;
		int solutionCost = solver.solve(graph);
		if (solutionCost > budget) {
			cout << "solution is too high" << endl;
			return 1;
		}
	}
	
	//cluster size = (vertices - hubSize / clusters)
	//min edges: (clusterSize - 1) * clusters
	//max edges: ((clusterSize * clusterSize - 1) / 2) * clusters	+ ((hubSize * hubSize - 1) / 2) + (clusterSize * budget * clusters) 
	//TODO: use computation to randomize instance generation a bit
	
	
	
	return 0;
}