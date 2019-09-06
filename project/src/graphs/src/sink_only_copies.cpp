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

void SinkOnlyCopies::contract(int originalVertex) {
	unordered_set<int> vertexInNeighbors = getInNeighbors(originalVertex);
	Graph::contract(originalVertex);
	int sinkCopy = getSink(originalVertex);
	Graph::remove(sinkCopy);
	//TODO: rather, remove those in contracted neighborhood...
	//removeArc(originalVertex, sinkCopy);
	sinkCopyMap.erase(originalVertex);
	for (int inNeighbor : vertexInNeighbors) {
		if (sinkCopyMap.count(inNeighbor)) {
			int inNeighborSink = sinkCopyMap[inNeighbor];
			removeArc(inNeighbor, inNeighborSink);
		}
	}
	
	
	
	//TODO: contract is not that easy... must avoid adding own sink as neighbor
	//TODO: query sink map and copy (also remove old sinks from map)
	//TODO: must also update sink map when normalizing..
}

unordered_map<int, int> SinkOnlyCopies::normalize() {
	unordered_map<int, int> oldToNew = Graph::normalize();
    unordered_map<int, int> newSinkCopyMap;
	for (const auto& entry : sinkCopyMap) {
		int newOriginal = oldToNew[entry.first];
		int newSink = oldToNew[entry.second];
		newSinkCopyMap.insert(make_pair(newOriginal, newSink));
	}
	sinkCopyMap = newSinkCopyMap;
	return oldToNew;
}

void SinkOnlyCopies::display() {
	Graph::display();
	for (const auto& entry : sinkCopyMap) {
		cout << "Vertex " << entry.first << " has sink only copy " << entry.second << endl;
	}
}




