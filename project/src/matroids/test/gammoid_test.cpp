#include "stdafx.h"
#include "carryless_multiplier_galois.h"
#include "naive_galois.h"
#include "matroid.h"
#include "gauss.h"
#include "dual_matroid.h"
#include "gammoid.h"
#include "transversal_matroid.h"

using namespace std;

const int repetitions = 1000;
const int edges = 200;
const int numberOfTerminals = 40;

int main(int argc, char* argv[]) {
	
	Galois* naiveGalois = new NaiveGalois(8);
	
	/*Matroid matroid(12, 8);
	
	for (int column = 0; column < matroid.getElements(); column++) {
		for (int row = 0; row < matroid.getRank(); row++) {
			bool zero = true;
			while (zero) {
				uint64_t value = naiveGalois -> uniformRandomElement();
				if (value != 0L) {
					matroid.setField(column, row, value);
					zero = false;
				}
			}
		}
	}
	Matroid dualMatroid = DualMatroid::generate(matroid, naiveGalois);*/

	//TODO: add very small test cases to find the issue

	//TODO: 4 independent vertices

	
	Graph graph1(4);
	unordered_set<int> sinks1;
	vector<int> sources1;
	for (int vertex = 0; vertex < graph1.getVertices(); vertex++) {
		sinks1.insert(vertex);
		sources1.push_back(vertex);
	}
	
	cout << endl << "gammoid1" << endl << endl;

	Matroid gammoid1 = Gammoid::generate(graph1, naiveGalois, sinks1);
	if (!gammoid1.isIndependent(sources1, naiveGalois)) {
		cout << "error: gammoid1 not independent!" << endl;
		return 1;
	}

	cout << endl << "gammoid2" << endl << endl;


	unordered_set<int> sinks2;
	vector<int> sources2;
	for (int vertex = 0; vertex < 3; vertex++) {
		sinks2.insert(vertex);
		sources2.push_back(vertex);
	}
	Matroid gammoid2 = Gammoid::generate(graph1, naiveGalois, sinks2);

	if (!gammoid2.isIndependent(sources2, naiveGalois)) {
		cout << "error: gammoid 2 not independent!" << endl;
		return 1;
	}

	vector<int> sources2a;
	sources2a.push_back(3);
	if (gammoid2.isIndependent(sources2a, naiveGalois)) {
		cout << "error: gammoid 2 non-sink independent!" << endl;
		return 1;
	}

	cout << endl << "gammoid3" << endl << endl;

	for (int vertex = 0; vertex < 3; vertex++) {
		graph1.addEdge(vertex, vertex + 1);
	}
	unordered_set<int> sinks3; 
	sinks3.insert(0);


	Matroid gammoid3 = Gammoid::generate(graph1, naiveGalois, sinks3);
	for (int vertex = 0; vertex < graph1.getVertices(); vertex++) {
		vector<int> sources3;
		sources3.push_back(vertex);
		if (!gammoid3.isIndependent(sources3, naiveGalois)) {
			cout << "gammoid 3 vertex " << vertex << " not independent!" << endl;
		}
	}
	if (gammoid3.getRank() != 1) {
		cout << "error: gammoid 3 rank is " << gammoid3.getRank() << endl;
		return 1;
	}
	
	cout << endl << "gammoid4" << endl << endl;

	Graph graph2(8);
	for (int i = 0; i < 3; i++) {
		graph2.addEdge(i, i + 1);
		graph2.addEdge(4 + i, 4 + i + 1);
	}
	unordered_set<int> sinks4;
	sinks4.insert(0);
	sinks4.insert(4);
	Matroid gammoid4 = Gammoid::generate(graph2, naiveGalois, sinks4);
	
	for (int i = 0; i < 4; i++) {
		for (int j = 4; j < 8; j++) {
			vector<int> sources4;
			sources4.push_back(i);
			sources4.push_back(j);
			if (!gammoid4.isIndependent(sources4, naiveGalois)) {
				cout << "gammoid 4 vertex " << i << " and " << j << " not independent!" << endl;
			}
		}
	}





	if (gammoid4.getRank() != 2) {
		cout << "error: gammoid 4 rank is " << gammoid4.getRank() << endl;
		return 1;
	}



	delete naiveGalois;



	//*
	
	int paths = 10;
	int pathLength = 10;

	Graph graph(paths * pathLength);
	unordered_set<int> sinks;
	vector<int> sources;
	//Galois* galois = new CarrylessMultiplierGalois();
	Galois* galois = new NaiveGalois(16);

	for (int path = 0; path < paths; path++) {
		for (int vertex = 0; vertex < 9; vertex++) {
			int pathVertex = (path * 10) + vertex;
			graph.addEdge(pathVertex, pathVertex + 1);
		}
		sinks.insert(path * pathLength);
		sources.push_back((path * pathLength) + pathLength - 1);//+ 9); //TODO: test with sinks first, then other points on path
	}



	cout << "generating matroid" << endl;

	
	Matroid gammoid = Gammoid::generate(graph, galois, sinks);
	if (!gammoid.isIndependent(sources, galois)) {
	cout << "not independent :(" << endl;
		return 1;
	}
	
	vector<int> sourcesx;
	sourcesx.push_back(0);
	sourcesx.push_back(pathLenght - 1);
	
	if (gammoid.isIndependent(sourcesx, galois)) {
		cout << "independent :(" << endl;
		return 1;
	}
	
	
	
	
	//TODO: create positive test cases 
	//hardcode a bunch of paths and add some noise
	
	
	//TODO: create negative test cases
	//??
	
	
	delete galois;

	//*/


	cout << "independent :)" << endl;

	return 0;
}
