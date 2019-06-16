#include "stdafx.h"
#include "independent_set.h"

using namespace std;

IndependentSet::IndependentSet(const int initRank, Galois* initGalois) : rank(initRank), galois(initGalois) {
	independentElements = 0;
	for (int row = 0; row < rank; row++) {
		nonZeroRows.insert(row);
	}
}

IndependentSet::~IndependentSet() {
}
	
bool IndependentSet::addColumn(vector<uint64_t> column) {
cout << "adding column" << endl;
	//if (independentElements == rank) {
//cout << "exceeds rank: not independent" << endl;
//		return false;
//	}
	for (int independentElement = 0; independentElement < independentElements; independentElement++) {
		applyPivot(independentElement, column);
	}
cout << "applied previous pivots" << endl;
for (int row = 0; row < rank; row++) {
string value = galois -> toString(column[row]);
cout << value << " ";
}
cout << endl;
	int pivotRow = findNonZeroRowIndex(column);
	if (pivotRow == -1) {
cout << "pivot not found: not independent" << endl;
		return false;
	}
	nonZeroRows.erase(pivotRow);
	independentColumns.push_back(column);
	independentElements++;
	pivots.push_back(pivotRow);
cout << "succesfully added element" << endl;
	return true;
}

void IndependentSet::applyPivot(int independentElement, vector<uint64_t>& column) {
	int pivot = pivots[independentElement];
cout << "applying pivot " << pivot << endl;
	if (column[pivot] == 0L) {
		return;
	}
	uint64_t divisor = independentColumns[independentElement][pivot];
	uint64_t ratio = galois -> divide(column[pivot], divisor);
	
	for (const auto& row : nonZeroRows) {
cout << "applying pivot " << pivot << " to row " << row << endl;
		uint64_t factor = galois -> multiply(independentColumns[independentElement][row], ratio);
		uint64_t oldFieldValue = column[row];
		uint64_t newFieldValue = galois -> add(oldFieldValue, factor);
//TODO: factor must relate to old column value on this particular row: this is wrong!
		column[row] = newFieldValue;
cout << "new value: " << newFieldValue << endl;
	}
}

int IndependentSet::findNonZeroRowIndex(vector<uint64_t> column) {
cout << "trying to find pivot with " << nonZeroRows.size() << " nonZero rows" << endl;
	for (const auto& row : nonZeroRows) {
cout << "checking row " << row << endl;
		if (column[row] != 0L) {
cout << "row is nonZero" << endl;
			return row;
		}
	}
cout << "couldn't find nonZero row" << endl;
	return -1;
}

