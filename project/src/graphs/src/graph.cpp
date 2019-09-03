#include "stdafx.h"
#include "graph.h"

using namespace std;

Graph::Graph(const int initVertices) {
	for (int vertex = 0; vertex < initVertices; vertex++) {
		unordered_set<int> vertexInNeighbors, vertexOutNeighbors;
		inNeighbors.push_back(vertexInNeighbors);
		outNeighbors.push_back(vertexOutNeighbors);
		vertices.insert(vertex);
	}
}

Graph::~Graph() {
}

void Graph::addEdge(int leftVertex, int rightVertex) {
	addArc(leftVertex, rightVertex);
	addArc(rightVertex, leftVertex);
}

void Graph::addArc(int inNeighbor, int outNeighbor) {
	outNeighbors[inNeighbor].insert(outNeighbor);
	inNeighbors[outNeighbor].insert(inNeighbor);
}

void Graph::addTerminal(int terminal) {
	terminals.insert(terminal);
}

bool Graph::isOutNeighbor(int vertex, int outNeighbor) {
	unordered_set<int> vertexOutNeighbors = outNeighbors[vertex];
	return vertexOutNeighbors.find(outNeighbor) != vertexOutNeighbors.end();
}

bool Graph::isInNeighbor(int vertex, int inNeighbor) {
	unordered_set<int> vertexInNeighbors = inNeighbors[vertex];
	return vertexInNeighbors.find(inNeighbor) != vertexInNeighbors.end();
}

bool Graph::isTerminal(int vertex) {
	return terminals.find(vertex) != terminals.end();
}

unordered_set<int> Graph::getTerminals() {
	return terminals;
}

unordered_set<int> Graph::getInNeighbors(int vertex) {
	return inNeighbors[vertex];
}

unordered_set<int> Graph::getOutNeighbors(int vertex) {
	return outNeighbors[vertex];
}

unordered_set<int> Graph::getVertices() {
	return vertices;
}

bool Graph::isIndependentSet() {
	for (int vertex : vertices) {
		if (!outNeighbors[vertex].empty()) {
			return false;
		}
		if (!inNeighbors[vertex].empty()) {
			return false;
		}
	}
	return true;
}

bool Graph::equals(Graph& otherGraph) {
	if (vertices != otherGraph.getVertices()) {
		return false;
	}
	if (terminals != otherGraph.getTerminals()) {
		return false;
	}
	for (int vertex : vertices) {
		if (getInNeighbors(vertex) != otherGraph.getInNeighbors(vertex)) {
			return false;
		}
		if (getOutNeighbors(vertex) != otherGraph.getOutNeighbors(vertex)) {
			return false;
		}
	}
	return true;
}