#include "stdafx.h"
#include "decorated_graph.h"

using namespace std;

DecoratedGraph::DecoratedGraph(Graph& graph, int initSuperSources) : Graph(graph.getVertices().size() * 2 - graph.getTerminals().size() + initSuperSources) {
	
	//TODO: don't give copies explicitly (take any vertex that is not in N[T])
	
	//sink only copies for all vertices that are not terminals
	
	//supersources connected to terminal neighbors
	//should supersources be connected to sink only copies? -> no because it bypasses the graph
	//keep all properties as invariant when contracting vertices
	//assume we never vertices in contract N(T)
	
	
	vector<int> sortedVertices;
	for (int vertex : graph.getVertices()) {
		sortedVertices.push_back(vertex);
	}
	sort(sortedVertices.begin(), sortedVertices.end());
	
	int index = graph.getVertices().size(); //TODO: fix index
	for (int vertex : sortedVertices) {
		for (int outNeighbor : graph.getOutNeighbors(vertex)) { //copy the graph
			addArc(vertex, outNeighbor);
		}
		if (graph.isTerminal(vertex)) {
			continue;
		}
		sinkCopyMap.insert(make_pair(vertex, index));
		for (int inNeighbor : graph.getInNeighbors(vertex)) {
			addArc(inNeighbor, index);
		}
		index++;
	}
	for (int terminal : graph.getTerminals()) {
		addTerminal(terminal);
	}	
	/*for (int copy : copies) {
		sinkCopyMap.insert(make_pair(copy, index));
		for (int inNeighbor : graph.getInNeighbors(copy)) {
			addArc(inNeighbor, index);
		}
		index++;
	}*/
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