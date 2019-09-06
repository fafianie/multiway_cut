#include "stdafx.h"
#include "graph.h"
#include "galois.h"
#include "matroid.h"
#include "dual_matroid.h"

using namespace std;

Matroid DualMatroid::generate(Matroid& inputMatroid, Galois* galois) {
	//unordered_set<int> elements = inputMatroid.getElements();
	//int rank = inputMatroid.getRank();
	//Matroid outputMatroid(inputMatroid); //TODO: allow inputMatroid to be destroyed to avoid work
	Matroid outputMatroid = inputMatroid;
	vector<int> orderedElements;
	for (int element : outputMatroid.getElements()) {
		orderedElements.push_back(element);
	}
	
	/*for (int column = 0; column < elements.size(); column++) {
		for (int row = 0; row < rank; row++) {	
			uint64_t value = inputMatroid.getField(column, row);
			outputMatroid.setField(column, row, value);
		}
	}*/
//cout << "input:" << endl;
//outputMatroid.display(orderedElements, galois);
	swipeDown(outputMatroid, orderedElements, galois);
//cout << "swiped down:" << endl;
//outputMatroid.display(orderedElements, galois);
	swipeUp(outputMatroid, orderedElements, galois);
//cout << "swiped up:" << endl;
//outputMatroid.display(orderedElements, galois);
	normalize(outputMatroid, orderedElements, galois);
//cout << "normalized:" << endl;
//outputMatroid.display(orderedElements, galois);
Matroid transposed = transpose(outputMatroid, orderedElements);
//cout << "transposed:" << endl;
//transposed.display(orderedElements, galois);

//cout << "returning dual matroid" << endl;
	return transposed;
}

void DualMatroid::swipeDown(Matroid& matroid, vector<int>& orderedElements, Galois* galois) {
	int size = matroid.getElements().size();
	int rank = matroid.getRank();
	int diagonal = min(size, rank);
	for (int index = 0; index < diagonal; index++) {
		int pivot = findPivot(matroid, orderedElements, index);
		if (pivot == -1) {
		cout << "Could not find pivot while swiping down";
			throw runtime_error("Could not find pivot while swiping down");
		}
		swapColumns(orderedElements, index, pivot);
		swipeRows(matroid, galois, orderedElements, index, index + 1, diagonal);
	}
}

void DualMatroid::swipeUp(Matroid& matroid, vector<int>& orderedElements, Galois* galois) {
	int size = matroid.getElements().size();
	int rank = matroid.getRank();
	int diagonal = min(size, rank);
	for (int index = 0; index < diagonal; index++) {
		int pivot = findPivot(matroid, orderedElements, index);
		if (pivot == -1) {
		cout << "Could not find pivot while swiping up";
			throw runtime_error("Could not find pivot while swiping up");
		}
		swapColumns(orderedElements, index, pivot);
		swipeRows(matroid, galois, orderedElements, index, 0, index);
	}
}

void DualMatroid::swipeRows(Matroid& matroid, Galois* galois, vector<int>& orderedElements, int pivotIndex, int firstRow, int lastRow) {
	int pivot = orderedElements[pivotIndex];
	uint64_t divisor = matroid.getField(pivot, pivotIndex);
	for (int row = firstRow; row < lastRow; row++) {
		if (matroid.getField(pivot, row) != 0L) {
			uint64_t ratio = galois -> divide(matroid.getField(pivot, row), divisor);
		
			for (int columnIndex = pivotIndex; columnIndex < orderedElements.size(); columnIndex++) {
				int column = orderedElements[columnIndex];
				uint64_t factor = galois -> multiply(matroid.getField(column, pivotIndex), ratio);
				uint64_t oldFieldValue = matroid.getField(column, row);
				uint64_t newFieldValue = galois -> add(oldFieldValue, factor);
				matroid.setField(column, row, newFieldValue);
			}
		}
	}
}

void DualMatroid::swapColumns(vector<int>& orderedElements, int leftIndex, int rightIndex) {
	if (leftIndex == rightIndex) {
		return;
	}
	int left = orderedElements[leftIndex];
	int right = orderedElements[rightIndex];
	orderedElements[leftIndex] = right;
	orderedElements[rightIndex] = left;
}

void DualMatroid::normalize(Matroid& matroid, vector<int>& orderedElements, Galois* galois) {
	for (int row = 0; row < matroid.getRank(); row++) {
		uint64_t divisor = matroid.getField(orderedElements[row], row);
		for (int columnIndex = matroid.getRank(); columnIndex < matroid.getElements().size(); columnIndex++) {
			int column = orderedElements[columnIndex];
			if (matroid.getField(column, row) != 0L) {
				uint64_t ratio = galois -> divide(matroid.getField(column, row), divisor);
				matroid.setField(column, row, ratio);
			}
		}
		matroid.setField(orderedElements[row], row, 1L);
	}
}

int DualMatroid::findPivot(Matroid& matroid, vector<int>& orderedElements, int row) {
	int candidate = row;
	while (candidate < orderedElements.size()) {
		if (matroid.getField(orderedElements[candidate], row) != 0L) {
			return candidate;
		}
		candidate++;
	}
	return -1;
}

Matroid DualMatroid::transpose(Matroid& matroid, vector<int>& orderedElements) {
	unordered_set<int> elements = matroid.getElements();
	int rank = matroid.getRank();
	int newRank = elements.size() - rank; 
	Matroid transposed(elements, newRank);
	for (int columnIndex = 0; columnIndex < rank; columnIndex++) {
		int newColumn = orderedElements[columnIndex];
		for (int newRow = 0; newRow < newRank; newRow++) {
			uint64_t newValue = matroid.getField(orderedElements[rank + newRow], columnIndex);
			transposed.setField(newColumn, newRow, newValue);
		}
	}
	for (int columnIndex = 0; columnIndex < newRank; columnIndex++) {
		int newColumn = orderedElements[columnIndex];
		transposed.setField(orderedElements[rank + columnIndex], columnIndex, 1);
	}
	return transposed;
}
