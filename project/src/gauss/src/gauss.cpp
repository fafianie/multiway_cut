#include "stdafx.h"
#include "galois.h"
#include "gauss.h"
#include "matroid.h"

using namespace std;

//TODO: replace with independent set class
//TODO: then implement stuff for dual matroid here
//TODO: basic matroid should have extract vector option
//TODO: avoid alias swaps if we can
bool Gauss::isIndependentSet(vector<int>& elements, 
							 Matroid matroid, 
							 Galois* galois) {
	if (matroid.getRank() < elements.size()) {
		return false;
	}
	unordered_set<int> nonZeroRows;
	for (int row = 0; row < matroid.getRank(); row++) {
		nonZeroRows.insert(row);
	}
	for (int elementIndex = 0; elementIndex < elements.size(); elementIndex++) {
		int pivotRow = Gauss::findNonZeroRowIndex(elements.at(elementIndex), nonZeroRows, matroid);
		if (pivotRow == -1) {
			return false; 
		}	
		if (!Gauss::swipeNonZeroRows(elementIndex, elements, pivotRow, nonZeroRows, matroid, galois)) {
			return false;
		}
		nonZeroRows.erase(pivotRow);
	}
	return true;
}

int Gauss::findNonZeroRowIndex(int element,
							   unordered_set<int>& nonZeroRows,
							   Matroid& matroid) {
	for (const auto& row : nonZeroRows) {
		if (matroid.getField(element, row) != 0L) {
			return row;
		}
	}
	return -1;
}

bool Gauss::swipeNonZeroRows(int startingElementIndex,
							 vector<int>& elements,
							 int pivotRow,
							 unordered_set<int>& nonZeroRows,
							 Matroid& matroid,
							 Galois* galois) {
	uint64_t divisor = matroid.getField(elements.at(startingElementIndex), pivotRow);
	for (int elementIndex = startingElementIndex + 1; elementIndex < elements.size(); elementIndex++) {
		int element = elements.at(elementIndex);
		if (matroid.getField(element, pivotRow) == 0L) {
			continue;
		}
		uint64_t ratio = galois -> divide(matroid.getField(element, pivotRow), divisor);
		bool foundNonZeroField = false;
		//TODO: capture in another function?
		for (const auto& row : nonZeroRows) {
			
			uint64_t oldFieldValue = matroid.getField(element, row);
			uint64_t factor = galois -> multiply(oldFieldValue, ratio);
			uint64_t newFieldValue = galois -> add(oldFieldValue, factor);
			if (newFieldValue != 0L) {
				foundNonZeroField = true;
			}
			matroid.setField(element, row, newFieldValue);
		}
		if (!foundNonZeroField) {
			return false;
		}
	}
	return true;
}

int Gauss::findPivot(vector<int>& elements, 
					int elementIndex, 
					Matroid& matroid) {
	int pivot = -1;
	for (int candidate = elementIndex; candidate < elements.size(); candidate++) {
		if (matroid.getField(elements.at(candidate), elementIndex) != 0L) {
			return candidate;
		}
	}
	return pivot;
}

//TODO: figure out what is happening here, can we just swap the aliases instead of everything?
//void Gauss::swapColumns(int element, 
//					 int otherElement, 
//					 int startingRow,
//					 int rows,
//					 Matroid& matroid) {
//	for (int row = startingRow; row < rows; row++) {
//		uint64_t oldValue = matroid.getField(element, row);
//		uint64_t otherOldValue = matroid.getField(otherElement, row);
//		matroid.setField(element, row, otherOldValue);
//		matroid.setField(otherElement, row, oldValue);
//	}
//	matroid.swapElements(element, otherElement);
//}









