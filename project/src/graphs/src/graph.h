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
		std::unordered_set<int> getVertices();
		std::unordered_set<int> getTerminals();
		std::unordered_set<int> getInNeighbors(int);
		std::unordered_set<int> getOutNeighbors(int);
		bool equals(Graph&);
		
		//TODO: contract operation
		
	private:
		std::unordered_set<int> vertices;
		std::unordered_set<int> terminals;
		std::vector<std::unordered_set<int>> inNeighbors;
		std::vector<std::unordered_set<int>> outNeighbors;
		
		//TODO: store active vertices as a vector .. don't resize adjacency matrix, update neighborhoods
		//TODO: see if we can live without adjacency matrix...
		//TODO: return all active vertices (as (un)ordered set?)
		
		
		
};
