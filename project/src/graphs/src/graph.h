#pragma once

#include "stdafx.h"

class Graph {

	public:
		Graph(const int);
		~Graph();
		
		bool isIndependentSet();
		void addEdge(int, int);
		void removeEdge(int, int);
		void addArc(int, int);
		void removeArc(int, int);
		void addTerminal(int);
		
		bool isOutNeighbor(int, int);
		bool isInNeighbor(int, int);
		bool isTerminal(int);
		std::unordered_set<int>& getVertices();
		std::unordered_set<int>& getTerminals();
		std::unordered_set<int>& getInNeighbors(int);
		std::unordered_set<int>& getOutNeighbors(int);
		bool equals(Graph&);
		void remove(int);
		void contract(int);
		std::unordered_map<int, int> normalize();
		void display();
		
	private:
		std::unordered_set<int> vertices;
		std::unordered_set<int> terminals;
		std::vector<std::unordered_set<int>> inNeighbors;
		std::vector<std::unordered_set<int>> outNeighbors;
};