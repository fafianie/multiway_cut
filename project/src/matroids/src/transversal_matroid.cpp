#include "stdafx.h"
#include "graph.h"
#include "galois.h"
#include "matroid.h"
#include "transversal_matroid.h"

using namespace std;

Matroid TransversalMatroid::generate(Graph& graph, Galois* galois, vector<int>& sinks) {
	int vertices = graph.getVertices();
cout << "creating transversal matroid with " << graph.getVertices() << " elements and " << sinks.size() << " sinks" << endl;
	Matroid matroid(vertices, sinks.size());
	for (int sinkIndex = 0; sinkIndex < sinks.size(); sinkIndex++) {
		for (int vertex = 0; vertex < vertices; vertex++) {
			if (graph.isOutNeighbor(sinks.at(sinkIndex), vertex)) {
				matroid.setField(vertex, sinkIndex, galois -> uniformRandomElement());
			}
		}
		cout << "sinkIndex: " << sinkIndex << ", sinks.at(sinkIndex): " << sinks.at(sinkIndex) << endl;
		matroid.setField(sinks.at(sinkIndex), sinkIndex, galois -> uniformRandomElement());
	}
	return matroid;
}
