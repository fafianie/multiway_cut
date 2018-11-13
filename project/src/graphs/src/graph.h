#pragma once

#include "stdafx.h"

class Graph {

	public:
		Graph(int);
		~Graph();
		
		bool isIndependentSet();
		void addEdge(int, int);
		void addTerminal(int);
		
		bool isOutNeighbor(int, int);
		bool isInNeighbor(int, int);
		bool isTerminal(int);
		int getVertices();
		int getEdges();
		int getNumberOfTerminals();
		std::unordered_set<int> getTerminals();
		
	private:
		bool **adjacent;
		int vertices;
		int edges;
		int numberOfTerminals;
		std::unordered_set<int> terminals;
};