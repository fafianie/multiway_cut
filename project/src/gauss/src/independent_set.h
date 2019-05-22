#pragma once

#include "stdafx.h"
#include "galois.h"
#include "matroid.h"

class IndependentSet {

	public:
		IndependentSet(int, Galois*);
		~IndependentSet();
		bool addColumn(std::vector<uint64_t>);

	private:
		int findNonZeroRowIndex(std::vector<uint64_t>);
		void applyPivot(int, std::vector<uint64_t>);
		std::vector<std::vector<uint64_t>> independentColumns;
		int rank;
		int independentElements;
		std::unordered_set<int> nonZeroRows;
		std::vector<int> pivots; //size equals independentElements
		Galois* galois;
};
