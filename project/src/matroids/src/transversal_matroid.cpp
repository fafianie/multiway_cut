#include "stdafx.h"
#include "graph.h"
#include "galois.h"
#include "matroid.h"
#include "transversal_matroid.h"

using namespace std;

Matroid TransversalMatroid::generate(Graph& graph, Galois* galois, vector<int>& sinks) {Matroid matroid(graph.getVertices(), sinks.size());
	for (int sinkIndex = 0; sinkIndex < sinks.size(); sinkIndex++) {
		for (int inNeighbor : graph.getInNeighbors(sinks.at(sinkIndex))) {
			matroid.setField(inNeighbor, sinkIndex, galois -> uniformRandomElement());
		}
		matroid.setField(sinks.at(sinkIndex), sinkIndex, galois -> uniformRandomElement());
	}
	return matroid;
}