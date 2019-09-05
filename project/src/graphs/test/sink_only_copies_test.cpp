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
	cout << "Created sink only copies. " << endl;
	sinkOnlyCopies.display();
	
	for (int u : graph.getVertices()) {
		for (int v : graph.getVertices()) {
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
	sinkOnlyCopies.contract(5);
	cout << "Contracted 5." << endl;
	sinkOnlyCopies.display();
	sinkOnlyCopies.normalize();
	cout << "Normalized." << endl;
	sinkOnlyCopies.display();
	
	Graph expectedGraph(11);
	expectedGraph.addEdge(0, 1);
	expectedGraph.addEdge(0, 2);
	expectedGraph.addEdge(1, 2);
	expectedGraph.addEdge(1, 5);
	expectedGraph.addEdge(2, 3);
	expectedGraph.addEdge(2, 4);
	expectedGraph.addEdge(2, 5);
	expectedGraph.addEdge(2, 6);
	expectedGraph.addEdge(3, 4);
	expectedGraph.addEdge(4, 5);
	expectedGraph.addEdge(4, 6);
	expectedGraph.addEdge(5, 6);
	expectedGraph.addEdge(6, 7);
	expectedGraph.addEdge(6, 8);
	expectedGraph.addEdge(7, 8);
	expectedGraph.addArc(0, 9);
	expectedGraph.addArc(1, 9);
	expectedGraph.addArc(3, 9);
	expectedGraph.addArc(4, 9);
	expectedGraph.addArc(5, 9);
	expectedGraph.addArc(6, 9);
	expectedGraph.addArc(6, 10);
	expectedGraph.addArc(8, 10);
	
	cout << "Created expected graph. " << endl;
	expectedGraph.display();
	
	if (!sinkOnlyCopies.equals(expectedGraph)) {
		cout << "Test error: sink only copies not equal to expected graph after applying operations" << endl;
		return 1;
	}
	if (sinkOnlyCopies.getSink(2) != 9) {
		cout << "Test error: sink only copy of 2 must be 9" << endl;
		return 1;
	}
	if (sinkOnlyCopies.getSink(7) != 10) {
		cout << "Test error : sink only copy of 7 must be 10" << endl;
		return 1;
	}	
	return 0;
}