#include "stdafx.h"
#include "sink_only_copies.h"

using namespace std;

SinkOnlyCopies::SinkOnlyCopies(Graph& graph, std::set<int>& copies) : Graph(graph.getVertices() + copies.size()) {
	int sink = graph.getVertices();
	for (int u = 0; u < graph.getVertices(); u++) {
		for (int v = 0; v < graph.getVertices(); v++) {
			if (graph.isOutNeighbor(u, v)) {
				addArc(u, v);
			}
		}
	}
	
	cout << "done copying adjacency" << endl;
	
	for (int copy : copies) {
		cout << "handling copy " << copy << endl;
		sinkCopyMap.insert(make_pair(copy, sink));
		for (int inNeighbor : graph.getInNeighbors(copy)) {
			addArc(inNeighbor, sink);
		}
		sink++;
	}
	
	cout << "done with sinkonly copies" << endl;
}

SinkOnlyCopies::~SinkOnlyCopies() {
}

int SinkOnlyCopies::getSink(int originalIndex) {
	return sinkCopyMap[originalIndex];
} 