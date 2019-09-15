#pragma once

#include "graph.h"
#include "decorated_graph.h"
#include "galois.h"
#include "matroid.h"

class MultiwayCutKernel {

	public:
		static Graph reduce(Graph&, int, int, int, Galois*);
		
	private:
		static bool contractVertex(Graph&, std::vector<DecoratedGraph>&, Matroid&, std::unordered_set<int>&, std::unordered_set<int>&, Galois*);
		static std::vector<uint64_t> sumColumn(int, int, Matroid&, std::vector<Matroid>&, Galois*);
		static std::vector<uint64_t> multiplyColumns(std::vector<uint64_t>&, std::stack<std::vector<uint64_t>>& columns, Galois* galois);
};