#include "stdafx.h"
#include "graph.h"
#include "half_integral_reduction.h"
#include "dgf_reader.h"
#include "multiway_cut_solver.h"

using namespace std;

int main(int argc, char* argv[]) {
	
	cout << "start test" << endl;
	vector<pair<string, int>> instances;
	instances.push_back({"1__star", 1});
	instances.push_back({"3__sparse_planar600_3", 3});
	instances.push_back({"10__sparse_codeminer_4", 10});
	instances.push_back({"11__sparse_fvs056_4", 11});
	//instances.push_back({"16__sparse_planar400_0", 16});
	//instances.push_back({"19__sparse_clh-10-1_3", 19});
	//instances.push_back({"19__sparse_hex_3", 19});
	//instances.push_back({"23__sparse_fvs100_4", 23});
	
	//MultiwayCutSolver* solver;
	for (pair<string, int> instance : instances) {
		cout << "start read" << endl;
		Graph graph = DGFReader::read("../../resources/test/correctness/", instance.first);	
		HalfIntegralReduction::reduce(graph);
		graph.normalize();
		cout << "graph read" << endl;
		MultiwayCutSolver solver;
		int solution = solver.solve(graph);
		if (solution != instance.second) {
			cout << "wrong answer" << endl;
			return 1;
		}
	}	
	cout <<  "all correct" << endl;
	return 0;
}