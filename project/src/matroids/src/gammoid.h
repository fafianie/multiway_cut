#pragma once

#include "matroid.h"
#include "graph.h"
#include "galois.h"

class Gammoid {
	
	public:
		static Matroid generate(Graph&, Galois*);
	
};