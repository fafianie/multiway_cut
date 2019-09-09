#pragma once

#include "stdafx.h"
#include "graph.h"

//TODO: rename and turn into general purpose mwc kernel graph
class DecoratedGraph : public Graph {

	public:
		DecoratedGraph(Graph&, std::set<int>&, int);
		~DecoratedGraph();
		int getSink(int);
		void contract(int);
		std::unordered_map<int, int> normalize();
		void display();
		std::unordered_set<int>& getSuperSources();
		
	private:
		std::unordered_map<int, int> sinkCopyMap;
		std::unordered_set<int> superSources;
};