#pragma once

#include "matroid.h"
#include "galois.h"

class UniformMatroid {
	
	public:
		static Matroid generate(int, int, Galois*);
};