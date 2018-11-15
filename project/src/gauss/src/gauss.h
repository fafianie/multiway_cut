#pragma once

#include "galois.h"
#include "matroid.h"

class Gauss{
	
	public:
		static bool isIndependentSet(std::vector<int>&, int, Matroid, Galois*);

	private:
		static void swapRows(int, int, int, int, Matroid&);
};