#pragma once

#include "stdafx.h"
#include "galois.h"
#include "matroid.h"

class IndependentSet {

	public:
		IndependentSet(int, Galois*);
		~IndependentSet();
		bool addColumn(uint64_t*);

	private:
		int findNonZeroRowIndex(uint64_t*);
		void applyPivot(int, uint64_t*);
		uint64_t** independentColumns;
		int rank;
		int independentElements;
		std::unordered_set<int> nonZeroRows;
		std::vector<int> pivots; //size equals independentElements
		Galois* galois;
};