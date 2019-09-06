#pragma once

#include "stdafx.h"
#include "graph.h"

class SinkOnlyCopies : public Graph {

	public:
		SinkOnlyCopies(Graph&, std::set<int>&);
		~SinkOnlyCopies();
		int getSink(int);
		void contract(int);
		std::unordered_map<int, int> normalize();
		void display();
		
	private:
		std::unordered_map<int, int> sinkCopyMap;
};