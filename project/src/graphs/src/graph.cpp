#include "stdafx.h"
#include "graph.h"

using namespace std;

Graph::Graph(const int initVertices) : vertices(initVertices), edges(0), numberOfTerminals(0) {
	adjacent.assign(vertices * vertices, false);
}

Graph::~Graph() {
}

void Graph::addEdge(int leftVertex, int rightVertex) {
	adjacent[vertices * leftVertex + rightVertex] = true;
	adjacent[vertices * rightVertex + leftVertex] = true;
	edges++;
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
