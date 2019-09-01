#include "stdafx.h"
#include "graph.h"
#include "sink_only_copies.h"

using namespace std;

int main(int argc, char* argv[]) {
	
	int vertices = 10;
	Graph graph(vertices);
	graph.addEdge(0, 1);
	graph.addEdge(0, 2);
	graph.addEdge(1, 2);
	graph.addEdge(1, 6);
	graph.addEdge(2, 3);
	graph.addEdge(2, 5);
	graph.addEdge(3, 4);
	graph.addEdge(4, 5);
	graph.addEdge(5, 6);
	graph.addEdge(5, 7);
	graph.addEdge(6, 7);
	graph.addEdge(7, 8);
	graph.addEdge(7, 9);
	graph.addEdge(8, 9);
	
	set<int> originals;
	originals.insert(2);
	originals.insert(5);
	originals.insert(8);
	

	SinkOnlyCopies sinkOnlyCopies(graph, originals);
	
	for (int u = 0; u < vertices; u++) {
		for (int v= 0; v < vertices; v++) {
			if (graph.isInNeighbor(u, v) != sinkOnlyCopies.isInNeighbor(u, v) || 
				graph.isOutNeighbor(u, v) != sinkOnlyCopies.isOutNeighbor(u, v)) {
					cout << "Test error: falsely copied adjacency of input graph" << endl;
					return 1;
			}
		}
	}
	for (int original : originals) {
		int copy = sinkOnlyCopies.getSink(original);
		if (!sinkOnlyCopies.getOutNeighbors(copy).empty()) {
			cout << "Test error: sinks should not have outNeighbors" << endl;
			return 1;
		}
		if (sinkOnlyCopies.getInNeighbors(copy) != graph.getInNeighbors(original)) {
			cout << "Test error: inNeighbors of copy do not match inNeighbors of input graph" << endl;
			return 1;
		}
	}
	
	return 0;
}