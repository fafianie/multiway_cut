#pragma once

#include "stdafx.h"

class Graph {

	public:
		Graph(int);
		~Graph();
		
		bool isIndependentSet();
		void addEdge(int, int);
		void addArc(int, int);
		void addTerminal(int);
		
		bool isOutNeighbor(int, int);
		bool isInNeighbor(int, int);
		bool isTerminal(int);
		int getVertices();
		int getEdges();
		int getNumberOfTerminals();
		std::unordered_set<int> getTerminals();
		std::unordered_set<int> getInNeighbors(int);
		std::unordered_set<int> getOutNeighbors(int);
		
	private:
		std::vector<bool> adjacent;
		int vertices;
		int edges;
		int numberOfTerminals;
		std::unordered_set<int> terminals;
		std::vector<std::unordered_set<int>> inNeighbors;
		std::vector<std::unordered_set<int>> outNeighbors;
};
