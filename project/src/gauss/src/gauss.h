#pragma once

#include "galois.h"
#include "matroid.h"

class Gauss{
	
	public:
		static bool isIndependentSet(std::vector<int>&, Matroid, Galois*);

	private:
	//	static void swapColumns(int, int, int, int, Matroid&);
		static int findPivot(std::vector<int>&, int, Matroid&);
		static int findNonZeroRowIndex(int,	std::unordered_set<int>&, Matroid&);
		static bool swipeNonZeroRows(int, std::vector<int>&, int, std::unordered_set<int>&, Matroid& matroid, Galois* galois);
};