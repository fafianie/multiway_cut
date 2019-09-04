#include "stdafx.h"
#include "graph.h"
#include "dgf_reader.h"

using namespace std;

int main(int argc, char* argv[]) {	
	Graph graph = DGFReader::read("../../resources/test/readers/", "reader_test");	
	if (graph.getVertices().size() != 10) {
		cout << "Error: incorrect number of vertices: " << graph.getVertices().size() << "." << endl;
		return 1;
	}
	if (graph.getTerminals().size() != 3) {
		cout << "Error: incorrect number of terminals." << endl;
		return 1;
	}
	if (!graph.isTerminal(1)) { 
		cout << "Error: vertex 1 must be a terminal." << endl;
		return 1;
	}
	if (!graph.isTerminal(5)) {
		cout << "Error: vertex 5 must be a terminal." << endl;
		return 1;
	}
	if (!graph.isTerminal(9)) {
		cout << "Error: vertex 9 must be a terminal." << endl;
		return 1;
	}
	for (int i : graph.getVertices()) {
		for (int j : graph.getVertices()) {
			if (i + 1 == j || i == j + 1) {
				if (!graph.isOutNeighbor(i, j)) {
					cout << "Error: vertex " << i << " must have out-neighbor " << j << "." << endl;
					return 1;
				}
				if (!graph.isInNeighbor(j, i)) {
					cout << "Error: vertex " << j << " must have in-neighbor " << i << "." << endl;
					return 1;
				}
			} else {
				if (graph.isOutNeighbor(i, j)) {
					cout << "Error: vertex " << i << " must not have out-neighbor " << j << "." << endl;
					return 1;
				}
				if (graph.isInNeighbor(j, i)) {
					cout << "Error: vertex " << j << " must not have in-neighbor " << i << "." << endl;
					return 1;
				}
			}			
		}
	}
	return 0;
}