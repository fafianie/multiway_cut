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
//	cout << "creating gammoid for graph with " << graph.getVertices() << " vertices" << endl;
	for (int vertex : graph.getVertices()) {
		if (sources.find(vertex) == sources.end()) {
			transversalSinks.push_back(vertex);
		}
	}
	Matroid transversal = TransversalMatroid::generate(graph, galois, transversalSinks);

	//cout << "created transversal" << endl;
	//transversal.display(galois);
	Matroid gammoid = DualMatroid::generate(transversal, galois);
	//cout << "created dual" << endl;
	//gammoid.display(galois);

//	cout << "returning gammoid" << endl;
	
	//TODO: see why deconstructing the transversal matroid fails
	//return transversal;
	return gammoid;
}
