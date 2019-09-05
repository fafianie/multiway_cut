#include "stdafx.h"
#include "graph.h"
#include "galois.h"
#include "matroid.h"
#include "transversal_matroid.h"

using namespace std;

Matroid TransversalMatroid::generate(Graph& graph, Galois* galois, vector<int>& sinks) {
//cout << "creating transversal matroid with " << graph.getVertices() << " elements and " << sinks.size() << " sinks" << endl;
	Matroid matroid(graph.getVertices(), sinks.size());
	for (int sinkIndex = 0; sinkIndex < sinks.size(); sinkIndex++) {
		for (int inNeighbor : graph.getInNeighbors(sinks.at(sinkIndex))) {
			matroid.setField(inNeighbor, sinkIndex, galois -> uniformRandomElement());
		}
//		cout << "sinkIndex: " << sinkIndex << ", sinks.at(sinkIndex): " << sinks.at(sinkIndex) << endl;
		matroid.setField(sinks.at(sinkIndex), sinkIndex, galois -> uniformRandomElement());
	}
	return matroid;
}
