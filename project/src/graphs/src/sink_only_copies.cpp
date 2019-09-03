#include "stdafx.h"
#include "sink_only_copies.h"

using namespace std;

SinkOnlyCopies::SinkOnlyCopies(Graph& graph, std::set<int>& copies) : Graph(graph.getVertices().size() + copies.size()) {
	int sink = graph.getVertices().size();
	for (int vertex : graph.getVertices()) {
		for (int outNeighbor: graph.getOutNeighbors(vertex)) {
			addArc(vertex, outNeighbor);
		}
	}
	
	for (int copy : copies) {
		sinkCopyMap.insert(make_pair(copy, sink));
		for (int inNeighbor : graph.getInNeighbors(copy)) {
			addArc(inNeighbor, sink);
		}
		sink++;
	}
}

SinkOnlyCopies::~SinkOnlyCopies() {
}

int SinkOnlyCopies::getSink(int originalIndex) {
	return sinkCopyMap[originalIndex];
} 