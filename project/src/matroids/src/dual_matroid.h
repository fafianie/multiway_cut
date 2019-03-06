#pragma once

#include "matroid.h"
#include "graph.h"
#include "galois.h"

class DualMatroid {
	
	public:
		static Matroid generate(Matroid&, Galois*);

};