#include "stdafx.h"
#include "graph.h"
#include "galois.h"
#include "matroid.h"
#include "transversal_matroid.h"

using namespace std;

Matroid TransversalMatroid::generate(Graph& graph, Galois* galois, vector<int>& sinks) {
	int vertices = graph.getVertices();
	Matroid matroid(vertices, sinks.size());
	for (int sinkIndex = 0; sinkIndex < sinks.size(); sinkIndex++) {
		for (int vertex = 0; vertex < vertices; vertex++) {
			if (graph.isOutNeighbor(sinks.at(sinkIndex), vertex)) {
				matroid.setField(vertex, sinkIndex, galois -> uniformRandomElement());
			}
		}
		matroid.setField(sinkIndex, sinks.at(sinkIndex), galois -> uniformRandomElement());
	}
	return matroid;
}