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

void Graph::removeEdge(int leftVertex, int rightVertex) {
	removeArc(leftVertex, rightVertex);
	removeArc(rightVertex, leftVertex);
}

void Graph::addArc(int inNeighbor, int outNeighbor) {
	outNeighbors[inNeighbor].insert(outNeighbor);
	inNeighbors[outNeighbor].insert(inNeighbor);
}

void Graph::removeArc(int inNeighbor, int outNeighbor) {
	outNeighbors[inNeighbor].erase(outNeighbor);
	inNeighbors[outNeighbor].erase(inNeighbor);
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

unordered_set<int>& Graph::getTerminals() {
	return terminals;
}

unordered_set<int>& Graph::getInNeighbors(int vertex) {
	return inNeighbors[vertex];
}

unordered_set<int>& Graph::getOutNeighbors(int vertex) {
	return outNeighbors[vertex];
}

unordered_set<int>& Graph::getVertices() {
	return vertices;
}

//TODO: test matroids, etc, with removal of vertices
//TODO: remember to remove sink copy when contracting (override in sinkonlycopy graph)
void Graph::remove(int vertex) {
	for (int outNeighbor : getOutNeighbors(vertex)) {
		inNeighbors[outNeighbor].erase(vertex);
	}
	for (int inNeighbor : getInNeighbors(vertex)) {
		outNeighbors[inNeighbor].erase(vertex);
	}
	vertices.erase(vertex);
	terminals.erase(vertex);
}

void Graph::contract(int vertex) {
	
	//TODO: implement taking edges vs arcs into account (make sure it does not break our sink only copies) should be the same?

	unordered_set<int> vertexInNeighbors = getInNeighbors(vertex);
	unordered_set<int> vertexOutNeighbors = getOutNeighbors(vertex);
	for (int inNeighbor : vertexInNeighbors) {
		for (int outNeighbor : vertexOutNeighbors) {
			if (inNeighbor != outNeighbor) {
				addArc(inNeighbor, outNeighbor);
			}
		}
	}
	remove(vertex);
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

map<int, int> Graph::normalize() { //TODO: output aliases?
	//std::unordered_set<int> vertices;
	//std::unordered_set<int> terminals;
	//std::vector<std::unordered_set<int>> inNeighbors;
	//std::vector<std::unordered_set<int>> outNeighbors;
	
	vector<int> oldVertices;
	for (int vertex : vertices) {
		oldVertices.push_back(vertex);
	}
	sort(oldVertices.begin(), oldVertices.end());
	
	unordered_set<int> newVertices, newTerminals;
	vector<unordered_set<int>> newInNeighbors, newOutNeighbors;
	
	map<int, int> oldToNew;
	
	int newVertex = 0;
	for (int oldVertex : oldVertices) {
		newVertices.insert(newVertex);
		oldToNew.insert(make_pair(oldVertex, newVertex));
		unordered_set<int> vertexInNeighbors, vertexOutNeighbors;
		newInNeighbors.push_back(vertexInNeighbors);
		newOutNeighbors.push_back(vertexOutNeighbors);
		newVertex++;
		//newvertex -> oldvertex from oldvertices
	}
	
	for (int oldVertex : oldVertices) {
		int newVertex = oldToNew[oldVertex];
		for (int oldInNeighbor : getInNeighbors(oldVertex)) {
			int newInNeighbor = oldToNew[oldInNeighbor];
			newInNeighbors[newVertex].insert(newInNeighbor);
			
			//need to go from old to new...
		}
		for (int oldOutNeighbor : getOutNeighbors(oldVertex)) {
			int newOutNeighbor = oldToNew[oldOutNeighbor];
			newOutNeighbors[newVertex].insert(newOutNeighbor);
		}
		if (isTerminal(oldVertex)) {
			newTerminals.insert(newVertex);
		}
	}

	vertices = newVertices;
	terminals = newTerminals;
	inNeighbors = newInNeighbors;
	outNeighbors = newOutNeighbors;
	return oldToNew;
}

void Graph::display() {
	vector<int> sortedVertices, sortedTerminals;
	for (int vertex : vertices) {
		sortedVertices.push_back(vertex);
	}
	for (int terminal : terminals) {
		sortedTerminals.push_back(terminal);
	}
	sort(sortedVertices.begin(), sortedVertices.end());
	sort(sortedTerminals.begin(), sortedTerminals.end());
	cout << endl << "Terminals: ";
	
	for (int terminal : sortedTerminals) {
		cout << terminal << " ";
	}
	cout << endl;
	for (int vertex : sortedVertices) {
		cout << "Vertex " << vertex << endl << "InNeighbors: ";
		for (int inNeighbor : getInNeighbors(vertex)) {
			cout << inNeighbor << " ";
		}
		cout << endl << "OutNeighbors: ";
		for (int outNeighbor : getOutNeighbors(vertex)) {
			cout << outNeighbor << " ";
		}
		cout << endl;
	}
	cout << endl;
}