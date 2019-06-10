#include "stdafx.h"
#include "carryless_multiplier_galois.h"
#include "naive_galois.h"
#include "matroid.h"
#include "gauss.h"
#include "dual_matroid.h"
#include "gammoid.h"
#include "transversal_matroid.h"

using namespace std;

const int verticesX = 50;
const int edgesX = 200;
const int numberOfSourcesX = 5;
const int pathLengthX = 5;
const int repetitionsX = 100;

struct pair_hash {
    inline size_t operator()(const pair<int,int> & v) const {
        return v.first * 31 + v.second;
    }
};

int main(int argc, char* argv[]) {
	
	Galois* galoisX = new CarrylessMultiplierGalois();
	
	int numberOfSourcesY = 2;
	
	Graph graphY(numberOfSourcesY * numberOfSourcesY);
	vector<int> sinksY;
	unordered_set<int> sourcesY;
	for (int sourceY = 0; sourceY < numberOfSourcesY; sourceY++) {
		sourcesY.insert(sourceY * numberOfSourcesY);
		sinksY.push_back(sourceY * numberOfSourcesY + numberOfSourcesY - 1);
	}
	for (int uY = 0; uY < graphY.getVertices(); uY++) {
		for (int vY = uY; vY < graphY.getVertices(); vY++) {
			graphY.addEdge(uY, vY);
		}
	}
	Matroid gammoidY = Gammoid::generate(graphY, galoisX, sourcesY);
	if (!gammoidY.isIndependent(sinksY, galoisX)) {
			cout << "not independent *************" << endl;
			return 1;
	}
	
	
	
	
	//TODO: test against cliques
	
	
	
	
	
	for (int repetitionX = 0; repetitionX < repetitionsX; repetitionX++) {
		Graph graphX(verticesX);
		vector<int> aliasesX;
		for (int vertexX = 0; vertexX < verticesX; vertexX++) {
			aliasesX.push_back(vertexX);
		}
		random_shuffle(aliasesX.begin(), aliasesX.end());
		unordered_set<int> sourcesX;
		vector<int> sinksX;
		unordered_set<pair<int, int>, pair_hash> edgeCandidatesX;
		for (int uX = 0; uX < verticesX; uX++) {
			for (int vX = uX; vX < verticesX; vX++) {
				pair<int, int> edgeCandidate(uX, vX);
				edgeCandidatesX.insert(edgeCandidate);
			}
		}	
		int offsetX = 0;
		for (int sourceX = 0; sourceX < numberOfSourcesX; sourceX++) {
			sourcesX.insert(aliasesX.at(offsetX));
			//sourcesX.insert(offsetX);
			cout << "source " << aliasesX.at(offsetX) << endl;
			//cout << "source " << offsetX << endl;
			
			for (int pathVertexX = 1; pathVertexX < pathLengthX; pathVertexX++) {
				int indexX = pathVertexX + offsetX;
				int currentVertexX = aliasesX.at(indexX);
				int previousVertexX = aliasesX.at(indexX - 1);
				cout << "pathVertex " << currentVertexX << " , previous " << previousVertexX << endl;
				//cout << "pathVertex " << indexX << " , previous " << (indexX - 1) << endl;
				graphX.addEdge(previousVertexX, currentVertexX);
			//	graphX.addEdge(indexX - 1, indexX);
				pair<int, int> blockedCandidateX(indexX - 1, indexX);
				edgeCandidatesX.erase(edgeCandidatesX.find(blockedCandidateX));
			}
			
			offsetX += pathLengthX;
			cout << "sink " << aliasesX.at(offsetX - 1) << endl;
			//cout << "sink " << (offsetX - 1) << endl;
			sinksX.push_back(aliasesX.at(offsetX - 1));
			//sinksX.push_back(offsetX - 1);
		}
		
		
		cout << "sources " << endl;
		for (auto sourceX : sourcesX) {
			cout << sourceX << endl;
		}
		cout << "sinks " << endl;
		for (auto sinkX : sinksX) {
			cout << sinkX << endl;
		}
		vector<pair<int, int>> shuffledEdgesX;
		for (auto edgeCandidateX : edgeCandidatesX) {
			shuffledEdgesX.push_back(edgeCandidateX);
		}
		random_shuffle(shuffledEdgesX.begin(), shuffledEdgesX.end());
		for (int edgeX = 0; edgeX < edgesX; edgeX++) {
			pair<int, int> edgeCandidateX = shuffledEdgesX.at(edgeX);
			int uX = aliasesX.at(edgeCandidateX.first);
			int vX = aliasesX.at(edgeCandidateX.second);
			cout << "add edge: " << uX << ", " << vX << endl;
			graphX.addEdge(uX, vX);
		}
		Matroid gammoidX = Gammoid::generate(graphX, galoisX, sourcesX);
		if (!gammoidX.isIndependent(sinksX, galoisX)) {
			cout << "not independent" << endl;
			return 1;
		}
	}
	
	
	
	
	
	
	
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
	sourcesx.push_back(pathLength - 1);
	
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
