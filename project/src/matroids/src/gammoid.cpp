#include "stdafx.h"
#include "graph.h"
#include "galois.h"
#include "matroid.h"
#include "gammoid.h"
#include "transversal_matroid.h"
#include "dual_matroid.h"

using namespace std;

Matroid Gammoid::generate(Graph& graph, Galois* galois) {
	vector<int> sinks;
	for (int vertex = 0; vertex < graph.getVertices(); vertex++) {
		if (graph.isTerminal(vertex)) {
			sinks.push_back(vertex);
		}
	}
	Matroid transversal = TransversalMatroid::generate(graph, galois, sinks);
	Matroid gammoid = DualMatroid::generate(transversal, galois);
	return gammoid;
}