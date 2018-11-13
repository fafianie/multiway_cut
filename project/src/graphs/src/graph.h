#pragma once

#include "stdafx.h"

class Graph {

	public:
		Graph(int);
		~Graph();
		
		bool isIndependentSet();
		void addEdge(int, int);
		void addTerminal(int);
		
	private:
		bool **adjacent;
		int vertices;
		int edges;
		int numberOfTerminals;
		std::vector<int> terminals;
};