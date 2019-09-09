#include "stdafx.h"
#include "independent_set.h"

using namespace std;

IndependentSet::IndependentSet(const int initRank, Galois* initGalois) : rank(initRank), galois(initGalois) {
	independentElements = 0;
}

IndependentSet::~IndependentSet() {
}
	
bool IndependentSet::addColumn(vector<uint64_t> column) {
	for (int row = 0; row < rank; row++) {
		nonZeroRows.insert(row);
	}
	for (int independentElement = 0; independentElement < independentElements; independentElement++) {
		applyPivot(independentElement, column);
	}
	int pivotRow = findNonZeroRowIndex(column);
	if (pivotRow == -1) {
		return false;
	}
	independentColumns.push_back(column);
	independentElements++;
	pivots.push_back(pivotRow);
	return true;
}

void IndependentSet::applyPivot(int independentElement, vector<uint64_t>& column) {
	int pivot = pivots[independentElement];
	if (column[pivot] == 0L) {
		return;
	}
	uint64_t divisor = independentColumns[independentElement][pivot];
	uint64_t ratio = galois -> divide(column[pivot], divisor);
	
	for (const auto& row : nonZeroRows) {
		uint64_t factor = galois -> multiply(independentColumns[independentElement][row], ratio);
		uint64_t oldFieldValue = column[row];
		uint64_t newFieldValue = galois -> add(oldFieldValue, factor);
		column[row] = newFieldValue;
	}
	nonZeroRows.erase(pivot);
}


int IndependentSet::findNonZeroRowIndex(vector<uint64_t>& column) {
	for (const auto& row : nonZeroRows) {
		if (column[row] != 0L) {
			return row;
		}
	}
	return -1;
}