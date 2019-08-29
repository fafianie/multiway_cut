#include "stdafx.h"
#include "sink_only_copies.h"

using namespace std;

SinkOnlyCopies::SinkOnlyCopies(Graph* graph, std::set<int>& copies) : Graph(graph -> getVertices() + copies.size()) {
	int sink = graph -> getVertices();
	for (int u = 0; u < graph -> getVertices(); u++) {
		for (int v = 0; v < graph -> getVertices(); v++) {
			if (graph -> isOutNeighbor(u, v)) {
				addArc(u, v);
			}
		}
	}
	
	for (int copy : copies) {
		sinkCopyMap.insert(make_pair(copy, sink));
		sink++;
		for (int inNeighbor : graph -> getInNeighbors(copy)) {
			addArc(inNeighbor, sink);
		}
	}
}

SinkOnlyCopies::~SinkOnlyCopies() {
}

SinkOnlyCopies::getCopy(int copy) {
	return sinkCopyMap[copy];
} 