#pragma once

#include "matroid.h"
#include "graph.h"
#include "galois.h"

class DualMatroid {
	
	public:
		static Matroid generate(Matroid&, Galois*);
	
	private:
		static void swipeDown(Matroid&, std::vector<int>&, Galois*);
		static void swipeUp(Matroid&, std::vector<int>&, Galois*);
		static void swapColumns(std::vector<int>&, int, int);
		static void normalize(Matroid&, std::vector<int>&, Galois*);
		static int findPivot(Matroid&, std::vector<int>&, int);
		static void swipeRows(Matroid&, Galois*, std::vector<int>&, int, int, int);
		static Matroid transpose(Matroid&, std::vector<int>&);
};