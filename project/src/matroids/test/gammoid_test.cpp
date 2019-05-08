#include "stdafx.h"
#include "carryless_multiplier_galois.h"
#include "naive_galois.h"
#include "matroid.h"
#include "gauss.h"
#include "dual_matroid.h"
#include "gammoid.h"

using namespace std;

const int repetitions = 1000;
const int edges = 200;
const int numberOfTerminals = 40;

int main(int argc, char* argv[]) {
	Galois* galois = new CarrylessMultiplierGalois();
	
	Matroid matroid(12, 8);
	
	for (int column = 0; column < matroid.getElements(); column++) {
		for (int row = 0; row < matroid.getRank(); row++) {
			bool zero = true;
			while (zero) {
				uint64_t value = galois -> uniformRandomElement();
				if (value != 0L) {
					matroid.setField(column, row, value);
					zero = false;
				}
			}
		}
	}

	Matroid dualMatroid = DualMatroid::generate(matroid, galois);

	Graph graph(100);
	unordered_set<int> sinks;
	vector<int> sources;
	
	for (int path = 0; path < 10; path++) {
		for (int vertex = 0; vertex < 9; vertex++) {
			int pathVertex = (path * 10) + vertex;
			graph.addEdge(pathVertex, pathVertex + 1);
		}
		sinks.insert(path * 10);
		sources.push_back((path * 10) + 9);
	}
	
	Matroid gammoid = Gammoid::generate(graph, galois, sinks);
	//if (!gammoid.isIndependent(sources, galois)) {
	//	return 1;
	//}
	
	
	
	
	
	
	//TODO: create positive test cases 
	//hardcode a bunch of paths and add some noise
	
	
	//TODO: create negative test cases
	//??
	
	
	
	
	
	
	
	delete galois;
	return 0;
}