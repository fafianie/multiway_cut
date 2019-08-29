#include "stdafx.h"
#include "sink_only_copies.h"

using namespace std;

SinkOnlyCopies::SinkOnlyCopies(Graph* graph, std::set<int>& copies) : Graph(graph -> getVertices() + copies.size()) {
	int index = graph -> getVertices();
	for (int u = 0; u < graph -> getVertices(); u++) {
		for (int v = 0; v < graph -> getVertices(); v++) {
			if (graph -> isOutNeighbor(u, v)) {
				addArc(u, v);
			}
		}
	}
	
	for (int copy : copies) {
		sinkCopyMap.insert(make_pair(copy, index));
		index++;
		//TODO: efficient way to find all in/out neighbors?
		//TODO: keep and update set of in/outneighbors for every vertex..
	}
	

//where should copies appear? (must be able to find them and original vertices)
//store indices of sink only copies in this object!
}

SinkOnlyCopies::~SinkOnlyCopies() {
}

SinkOnlyCopies::getCopy(int copy) {
	return sinkCopyMap[copy];
} 