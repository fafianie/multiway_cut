#include "stdafx.h"
#include "independent_set.h"

using namespace std;

IndependentSet::IndependentSet(const int initRank, Galois* initGalois) : rank(initRank), galois(initGalois) {
	independentColumns = new uint64_t*[rank];
	independentElements = 0;
	for (int row = 0; row < rank; row++) {
		nonZeroRows.insert(row);
	}
}

IndependentSet::~IndependentSet() {
	for (int column = 0; column < independentElements; column++) {
		delete[] independentColumns[column];
	}
	delete[] independentColumns;
}
	
bool IndependentSet::addColumn(uint64_t* column) {
	if (independentElements == rank) {
		return false;
	}
	uint64_t* newColumn = new uint64_t[rank];
	for (const auto &row : nonZeroRows) {
		newColumn[row] = column[row];
	}
	for (int independentElement = 0; independentElement < independentElements; independentElement++) {
		applyPivot(independentElement, newColumn);
	}
	int pivotRow = findNonZeroRowIndex(newColumn);
	if (pivotRow == -1) {
		return false;
	}
	nonZeroRows.erase(pivotRow);
	independentColumns[independentElements] = newColumn;
	independentColumns++;
	pivots.push_back(pivotRow);
	return true;
}

void IndependentSet::applyPivot(int independentElement, uint64_t* column) {
	int pivot = pivots[independentElement];
	if (column[pivot] == 0L) {
		return;
	}
	uint64_t divisor = independentColumns[independentElement][pivot];
	uint64_t ratio = galois -> divide(column[pivot], divisor);
	for (const auto& row : nonZeroRows) {
		uint64_t oldFieldValue = column[row];
		uint64_t factor = galois -> multiply(oldFieldValue, ratio);
		uint64_t newFieldValue = galois -> add(oldFieldValue, factor);
		column[row] = newFieldValue;
	}
}

int IndependentSet::findNonZeroRowIndex(uint64_t* column) {
	for (const auto& row : nonZeroRows) {
		if (column[row] != 0L) {
			return row;
		}
	}
	return -1;
}

