#include "stdafx.h"
#include "graph.h"
#include "galois.h"
#include "matroid.h"
#include "gammoid.h"
#include "transversal_matroid.h"
#include "dual_matroid.h"

using namespace std;

Matroid Gammoid::generate(Graph& graph, Galois* galois, unordered_set<int> sources) {
	vector<int> transversalSinks;
	for (int vertex : graph.getVertices()) {
		if (sources.find(vertex) == sources.end()) {
			transversalSinks.push_back(vertex);
		}
	}
	Matroid transversal = TransversalMatroid::generate(graph, galois, transversalSinks);
	Matroid gammoid = DualMatroid::generate(transversal, galois);
	return gammoid;
}