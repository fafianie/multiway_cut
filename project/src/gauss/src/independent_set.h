#pragma once

#include "stdafx.h"
#include "galois.h"
#include "matroid.h"

class IndependentSet {

	public:
		IndependentSet(int, Galois*);
		~IndependentSet();
		bool addColumn(std::vector<uint64_t>); //TODO: pass reference?

	private:
		int findNonZeroRowIndex(std::vector<uint64_t>&);
		void applyPivot(int, std::vector<uint64_t>&);
		
		std::vector<std::vector<uint64_t>> independentColumns;
		int rank;
		int independentElements;
		std::set<int> nonZeroRows;
		std::vector<int> pivots;
		Galois* galois;
};