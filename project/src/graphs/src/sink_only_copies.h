#pragma once

#include "stdafx.h"
#include "graph.h"

class SinkOnlyCopies : public Graph {

	public:
		SinkOnlyCopies(Graph&, std::set<int>&);
		~SinkOnlyCopies();
		int getCopy(int);
		
	private:
		std::map<int, int> sinkCopyMap;
};