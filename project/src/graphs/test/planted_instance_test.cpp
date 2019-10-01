#include "stdafx.h"
#include "graph.h"
#include "multiway_cut_solver.h"

using namespace std;

int main(int argc, char* argv[]) {
	int vertices, clusters, terminals, edges, hubSize, hubEdges, budget;
	
	vertices = 100;
	clusters = 4;
	terminals = 3;
	edges = ;
	hubSize = 10;
	hubEdges = 20;
	budget = 3;

	PlantedInstance graph(vertices, clusters, terminals, edges, hubSize, hubEdges, budget);
	
	MultiwayCutSolver solver;
	if (solver.solve(graph) > budget) {
		cout << "solution is too high" << endl;
	}
	return 1;
	
	vertices = 0;
	clusters = 0;
	terminals = 0;
	edges = 0;
	hubSize = 0;
	hubEdges = 0;
	budget = 4;

	PlantedInstance graph(vertices, clusters, terminals, edges, hubSize, hubEdges, budget);
	
	MultiwayCutSolver solver;
	if (solver.solve(graph) > budget) {
		cout << "solution is too high" << endl;
	}
	return 1;
	
	vertices = 0;
	clusters = 0;
	terminals = 0;
	edges = 0;
	hubSize = 0;
	hubEdges = 0;
	budget = 5;

	PlantedInstance graph(vertices, clusters, terminals, edges, hubSize, hubEdges, budget);
	
	MultiwayCutSolver solver;
	if (solver.solve(graph) > budget) {
		cout << "solution is too high" << endl;
	}
	return 1;
	
	vertices = 0;
	clusters = 0;
	terminals = 0;
	edges = 0;
	hubSize = 0;
	hubEdges = 0;
	budget = 6;

	PlantedInstance graph(vertices, clusters, terminals, edges, hubSize, hubEdges, budget);
	
	MultiwayCutSolver solver;
	if (solver.solve(graph) > budget) {
		cout << "solution is too high" << endl;
	}
	return 1;
	

	return 0;
}