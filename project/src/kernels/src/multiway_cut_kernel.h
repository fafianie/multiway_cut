#pragma once

#include "graph.h"
#include "decorated_graph.h"
#include "galois.h"
#include "matroid.h"

class MultiwayCutKernel {

	public:
		MultiwayCutKernel();
		~MultiwayCutKernel();
		
		Graph reduce(Graph&, int, Galois*);
		
	private:
		bool contractVertex(Graph&, DecoratedGraph&, Matroid&, std::unordered_set<int>&, std::unordered_set<int>&, Galois*);
		std::vector<uint64_t> sumColumn(int, int, Matroid&, std::vector<Matroid>&, Galois*);
		std::vector<uint64_t> multiplyColumns(std::vector<uint64_t>&, std::stack<std::vector<uint64_t>>& columns, Galois* galois);
};