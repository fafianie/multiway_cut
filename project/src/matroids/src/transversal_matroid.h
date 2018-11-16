#pragma once

#include "matroid.h"
#include "graph.h"
#include "galois.h"

class TransversalMatroid {
	
	public:
		static Matroid generate(Graph&, Galois*, std::vector<int>&);

};