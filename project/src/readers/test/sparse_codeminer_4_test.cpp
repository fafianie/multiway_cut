#include "stdafx.h"
#include "graph.h"
//#include "planted_instance.h"
//#include "mwcsolver.h"
#include "dgf_reader.h"

using namespace std;

int main(int argc, char* argv[]) {
	
	cout << "start test" << endl;
	vector<pair<string, int>> instances;
	//instances.push_back({"3__sparse_planar600_3", 3});
	instances.push_back({"10__sparse_codeminer_4", 10});
	//instances.push_back({"11__sparse_fvs056_4", 11});
	//instances.push_back({"16__sparse_planar400_0", 16});
	//instances.push_back({"19__sparse_clh-10-1_3", 19});
	//instances.push_back({"19__sparse_hex_3", 19});
	//instances.push_back({"23__sparse_fvs100_4", 23});
	
	cout << "before loop" << endl;
	
	//MWCSolver* solver;
	for (pair<string, int> instance : instances) {
		cout << "start read" << endl;
		//TODO: PROBLEM IS HERE
		Graph graph = DGFReader::read("../../resources/test/correctness/", instance.first);	
		
		cout << "graph is loaded" << endl;
		
	
		/*MWCSolver* solver = new MWCSolver();
		cout << "solver created" << endl;
		int solution = solver -> solve(graph);
		cout << "solution retrieved" << endl;
		if (!(solution == instance.second)) {
			return 1;
		}
	
		delete solver;*/
		
	}	
	
	return 0;
}