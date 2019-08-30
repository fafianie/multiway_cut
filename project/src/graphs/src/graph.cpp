#include "stdafx.h"
#include "graph.h"

using namespace std;

Graph::Graph(const int initVertices) : vertices(initVertices), edges(0), numberOfTerminals(0) {
	adjacent.assign(vertices * vertices, false);
	for (int vertex = 0; vertex < vertices; vertex++) {
		unordered_set<int> vertexInNeighbors, vertexOutNeighbors;
		inNeighbors.push_back(vertexInNeighbors);
		outNeighbors.push_back(vertexOutNeighbors);
	}
}

Graph::~Graph() {
}

void Graph::addEdge(int leftVertex, int rightVertex) {
	addArc(leftVertex, rightVertex);
	addArc(rightVertex, leftVertex);
	edges++;
}

void Graph::addArc(int inNeighbor, int outNeighbor) {
	adjacent[vertices * inNeighbor + outNeighbor] = true;
	outNeighbors[inNeighbor].insert(outNeighbor);
	inNeighbors[outNeighbor].insert(inNeighbor);
}

void Graph::addTerminal(int terminal) {
	terminals.insert(terminal);
	numberOfTerminals++;
}

bool Graph::isOutNeighbor(int vertex, int outNeighbor) {
	return adjacent[vertices * vertex + outNeighbor];
}

bool Graph::isInNeighbor(int vertex, int inNeighbor) {
	return adjacent[vertices * inNeighbor + vertex];
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

int Graph::getVertices() {
	return vertices;
}

int Graph::getEdges() {
	return edges;
}

int Graph::getNumberOfTerminals() {
	return numberOfTerminals;
}

bool Graph::isIndependentSet() {
	for (int i = 0; i < vertices; i++) {
		for(int j = 0; j < vertices; j++) {
			if (adjacent[vertices * i + j]) {
				return false;
			}
		}
	}
	return true;
}

bool Graph::equals(Graph& otherGraph) {
	if (vertices != otherGraph.getVertices()) {
		return false;
	}
	if (edges != otherGraph.getEdges()) {
		return false;
	}
	if (terminals != otherGraph.getTerminals()) {
		return false;
	}
	for (int u = 0; u < vertices; u++) {
		for (int v = 0; v < vertices; v++) {
			if (isInNeighbor(u, v) != otherGraph.isInNeighbor(u, v) ||
				isOutNeighbor(u, v) != otherGraph.isOutNeighbor(u, v)) {
				return false;
			}
		}
	}
	return true;
}