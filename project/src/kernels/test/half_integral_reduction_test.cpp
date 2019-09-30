#include "stdafx.h"
#include "graph.h"
#include "half_integral_reduction.h"
#include "dgf_reader.h"
#include "multiway_cut_solver.h"

using namespace std;

int main(int argc, char* argv[]) {

	Graph graph = DGFReader::read("../../resources/test/correctness/", "3__sparse_planar600_3");	
	HalfIntegralReduction::reduce(graph);
	graph.normalize();
	MultiwayCutSolver solver;
	int solution = solver.solve(graph);
	cout << "solution of reduced instance: " << solution << endl;
	
	if (solution != 3) {
		return 1;
	}

	return 0;
}