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
	terminals.push_back(terminal);
	numberOfTerminals++;
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