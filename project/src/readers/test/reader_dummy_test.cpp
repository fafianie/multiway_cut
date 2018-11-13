#include "stdafx.h"
#include "graph.h"
#include "dfg_reader.h"

using namespace std;

int main(int argc, char* argv[]) {

	Graph graph = DFGReader::read("../../resources/test/readers/", "reader_dummy_test.dgf");
	
	if (graph.getVertices() != 10) {
		return 1;
	}
	if (graph.getEdges() != 16) {
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
	
	//TODO: EXTEND TEST? CHECK EDGES
	return 0;
}