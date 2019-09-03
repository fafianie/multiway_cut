#pragma once

#include "graph.h"

class MultiwayCutKernel {

	public:
		MultiwayCutKernel();
		~MultiwayCutKernel();
		
		Graph reduce(Graph&);
		
	private:
		bool contractVertex(Graph&);
};

