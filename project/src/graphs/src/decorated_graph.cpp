#include "stdafx.h"
#include "decorated_graph.h"

using namespace std;

DecoratedGraph::DecoratedGraph(Graph& graph, std::set<int>& copies, int initSuperSources) : Graph(graph.getVertices().size() + copies.size() + initSuperSources) {
	
	//TODO: don't give copies explicitly (take any vertex that is not in N[T])
	
	int index = graph.getVertices().size();
	for (int vertex : graph.getVertices()) {
		for (int outNeighbor: graph.getOutNeighbors(vertex)) {
			addArc(vertex, outNeighbor);
		}
	}
	for (int terminal : graph.getTerminals()) {
		addTerminal(terminal);
	}	
	for (int copy : copies) {
		sinkCopyMap.insert(make_pair(copy, index));
		for (int inNeighbor : graph.getInNeighbors(copy)) {
			addArc(inNeighbor, index);
		}
		index++;
	}
	for (int superSourceIndex = 0; superSourceIndex < initSuperSources; superSourceIndex++) {
		superSources.insert(index);
		for (int terminal : getTerminals()) {
			for (int outNeighbor : graph.getOutNeighbors(terminal)) {
				addArc(index, outNeighbor);
			}
		}
		index++;
	}
	//TODO: connect superSources to sink only copies???
}

DecoratedGraph::~DecoratedGraph() {
}

int DecoratedGraph::getSink(int originalIndex) {
	return sinkCopyMap[originalIndex];
} 

unordered_set<int>& DecoratedGraph::getSuperSources() {
	return superSources;
}

void DecoratedGraph::contract(int originalVertex) {
	unordered_set<int>& vertexInNeighbors = getInNeighbors(originalVertex);
	Graph::contract(originalVertex);
	int sinkCopy = getSink(originalVertex);
	Graph::remove(sinkCopy);
	sinkCopyMap.erase(originalVertex);
	for (int inNeighbor : vertexInNeighbors) {
		if (sinkCopyMap.count(inNeighbor)) {
			int inNeighborSink = sinkCopyMap[inNeighbor];
			removeArc(inNeighbor, inNeighborSink);
		}
	}
}

unordered_map<int, int> DecoratedGraph::normalize() {
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

void DecoratedGraph::display() {
	Graph::display();
	for (const auto& entry : sinkCopyMap) {
		cout << "Vertex " << entry.first << " has sink only copy " << entry.second << endl;
	}
}