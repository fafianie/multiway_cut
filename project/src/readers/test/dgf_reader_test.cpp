#include "stdafx.h"
#include "graph.h"
#include "dgf_reader.h"

using namespace std;

int main(int argc, char* argv[]) {	
	Graph graph = DGFReader::read("../../resources/test/readers/", "reader_test");	
	if (graph.getVertices() != 10) {
		return 1;
	}
	if (graph.getEdges() != 9) {
		return 1;
	}
	if (graph.getNumberOfTerminals() != 3) {
		return 1;
	}
	if (!graph.isTerminal(1)) { 
		return 1;
	}
	if (!graph.isTerminal(5)) {
		return 1;
	}
	if (!graph.isTerminal(9)) {
		return 1;
	}
	for (int i = 0; i < graph.getVertices(); i++) {
		for (int j = i; j < graph.getVertices(); j++) {
			if (i + 1 == j) {
				if (!graph.isOutNeighbor(i, j)) {
					return 1;
				}
				if (!graph.isInNeighbor(j, i)) {
					return 1;
				}
			} else {
				if (graph.isOutNeighbor(i, j)) {
					return 1;
				}
				if (graph.isInNeighbor(j, i)) {
					return 1;
				}
			}			
		}
	}
	return 0;
}