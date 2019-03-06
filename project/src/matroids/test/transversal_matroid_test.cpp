#include "stdafx.h"
#include "carryless_multiplier_galois.h"
#include "matroid.h"
#include "transversal_matroid.h"
#include "independent_set.h"

using namespace std;

const int repetitions = 1000;
const int edges = 200;
const int numberOfSinks = 40;

int main(int argc, char* argv[]) {
	Galois* galois = new CarrylessMultiplierGalois();
	vector<int> sinks;
	for (int sink = 0; sink < numberOfSinks; sink++) {
		sinks.push_back(sink);
	}
	for (int repetition = 0; repetition < repetitions; repetition++) {
		Graph graph(2 * numberOfSinks);
		random_shuffle(sinks.begin(), sinks.end());
		
		for (int sink = 0; sink < numberOfSinks; sink++) {
			graph.addEdge(sinks.at(sink), numberOfSinks + sink);
		};
		Matroid matroid = TransversalMatroid::generate(graph, galois, sinks);
		
		bool independent = matroid.isIndependent(sinks, galois);
		
		if (!independent) {
			cout << "dependent" << endl;
			return 1;
		}
		cout << "independent" << endl;
	}

	//TEST POSITIVE BY GENERATING GRAPHS WITH PLANTED MATCHINGS
	
	//TEST NEGATIVE BY GENERATING GRAPHS THAT DON"T HAVE ENOUGH COMMON NEIGHBORS
	
	
	delete galois;
	return 0;
}