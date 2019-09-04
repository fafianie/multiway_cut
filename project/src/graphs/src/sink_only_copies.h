#pragma once

#include "stdafx.h"
#include "graph.h"

class SinkOnlyCopies : public Graph {

	public:
		SinkOnlyCopies(Graph&, std::set<int>&);
		~SinkOnlyCopies();
		int getSink(int);
		void contract(int);
		std::map<int, int> normalize();
		
	private:
		std::map<int, int> sinkCopyMap;
};