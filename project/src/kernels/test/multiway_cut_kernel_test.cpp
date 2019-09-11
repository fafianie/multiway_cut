#include "stdafx.h"
#include "graph.h"
#include "multiway_cut_kernel.h"
#include "dgf_reader.h"
#include "carryless_multiplier_galois.h"
#include "multiway_cut_solver.h"

using namespace std;

int main(int argc, char* argv[]) {


	//TODO: create small example graph, just get it to complete first, then debug bigger graphs.
	Graph graph = DGFReader::read("../../resources/test/correctness/", "3__sparse_planar600_3");	
	/*Graph graph(8);
	graph.addEdge(0, 1);
	graph.addEdge(0, 2);
	graph.addEdge(0, 3);
	graph.addEdge(0, 4);
	graph.addEdge(1, 5);
	graph.addEdge(2, 5);
	graph.addEdge(3, 6);
	graph.addEdge(4, 6);
	graph.addEdge(5, 7);
	graph.addEdge(6, 7);
	graph.addTerminal(0);
	graph.addTerminal(7);*/
	//solution: k = 2: {5, 6}
	
	
	Galois* galois = new CarrylessMultiplierGalois();
	Graph reducedGraph = MultiwayCutKernel::reduce(graph, 3, galois);
	
	MultiwayCutSolver solver;
	int solution = solver.solve(graph);
	cout << "solution of reduced instance: " << solution << endl;
	
	
	delete galois;
	return 0;
}