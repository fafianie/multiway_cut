#include "stdafx.h"
#include "graph.h"

using namespace std;

Graph::Graph(const int initVertices) : vertices(initVertices), edges(0), numberOfTerminals(0) {
	adjacent = new bool*[vertices];
	for (int i = 0; i < vertices; i++) {
		adjacent[i] = new bool[vertices];
		for (int j = 0; j < vertices; j++) {
			adjacent[i][j] = false;
		}
	}
}

Graph::~Graph() {
	for (int i = 0; i < vertices; i++) {
		delete[] adjacent[i];
	}
	delete[] adjacent;
}

void Graph::addEdge(int leftVertex, int rightVertex) {
	adjacent[leftVertex][rightVertex] = true;
	adjacent[rightVertex][leftVertex] = true;
	edges++;
}

void Graph::addTerminal(int terminal) {
	terminals.insert(terminal);
	numberOfTerminals++;
}

bool Graph::isOutNeighbor(int vertex, int outNeighbor) {
	return adjacent[vertex][outNeighbor];
}

bool Graph::isInNeighbor(int vertex, int inNeighbor) {
	return adjacent[inNeighbor][vertex];
}

bool Graph::isTerminal(int vertex) {
	return terminals.find(vertex) != terminals.end();
}

unordered_set<int> Graph::getTerminals() {
	return terminals;
}

vector<

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
			if (adjacent[i][j]) {
				return false;
			}
		}
	}
	return true;
}