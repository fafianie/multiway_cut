#include "stdafx.h"
#include "graph.h"
#include "galois.h"
#include "matroid.h"
#include "dual_matroid.h"

using namespace std;

Matroid DualMatroid::generate(Matroid& inputMatroid, Galois* galois) {
	int elements = inputMatroid.getElements();
	int rank = inputMatroid.getRank();
	Matroid outputMatroid(elements, rank);
	for (int column = 0; column < elements; column++) {
		for (int row = 0; row < rank; row++) {	
			uint64_t value = inputMatroid.getField(column, row);
			outputMatroid.setField(column, row, value);
		}
	}
cout << "input:" << endl;
outputMatroid.display(galois);
	swipeDown(outputMatroid, galois);
cout << "swiped down:" << endl;
outputMatroid.display(galois);
	swipeUp(outputMatroid, galois);
cout << "swiped up:" << endl;
outputMatroid.display(galois);
	normalize(outputMatroid, galois);
cout << "normalized:" << endl;
outputMatroid.display(galois);
Matroid transposed = transpose(outputMatroid);
cout << "transposed:" << endl;
transposed.display(galois);

cout << "returning dual matroid" << endl;
	return transposed;
}

void DualMatroid::swipeDown(Matroid& matroid, Galois* galois) {
	int elements = matroid.getElements();
	int rank = matroid.getRank();
	int diagonal = min(elements, rank);
	for (int currentColumn = 0; currentColumn < diagonal; currentColumn++) {
		int pivot = findPivot(matroid, currentColumn);
		if (pivot == -1) {
			throw runtime_error("Could not find pivot while swiping down");
		}
		matroid.swapElements(currentColumn, pivot);
		swipeRows(matroid, galois, currentColumn, currentColumn + 1, diagonal - 1);
	}
}

void DualMatroid::swipeUp(Matroid& matroid, Galois* galois) {
	int elements = matroid.getElements();
	int rank = matroid.getRank();
	int diagonal = min(elements, rank);
	for (int currentColumn = 0; currentColumn < diagonal; currentColumn++) {
		int pivot = findPivot(matroid, currentColumn);
		if (pivot == -1) {
			throw runtime_error("Could not find pivot while swiping up");
		}
		matroid.swapElements(currentColumn, pivot);
		swipeRows(matroid, galois, currentColumn, 0, currentColumn -1);
	}
}

void DualMatroid::normalize(Matroid& matroid, Galois* galois) {
	for (int row = 0; row < matroid.getRank(); row++) {
		uint64_t divisor = matroid.getField(row, row);
		for (int column = matroid.getRank(); column < matroid.getElements(); column++) {
			if (matroid.getField(column, row) != 0L) {
				uint64_t ratio = galois -> divide(matroid.getField(column, row), divisor);
				matroid.setField(column, row, ratio);
			}
		}
		matroid.setField(row, row, 1L);
	}
}

int DualMatroid::findPivot(Matroid& matroid, int row) {
	int candidate = row;
	while (candidate < matroid.getElements()) {
		if (matroid.getField(candidate, row) != 0L) {
			return candidate;
		}
		candidate++;
	}
	return -1;
}

void DualMatroid::swipeRows(Matroid& matroid, Galois* galois, int pivot, int firstRow, int lastRow) {
	uint64_t divisor = matroid.getField(pivot, pivot);
	for (int row = firstRow; row <= lastRow; row++) {
		if (matroid.getField(pivot, row) != 0L) {
			uint64_t ratio = galois -> divide(matroid.getField(pivot, row), divisor);
			
			for (int column = pivot; column < matroid.getElements(); column++) {
				uint64_t factor = galois -> multiply(matroid.getField(column, pivot), ratio);
				uint64_t oldFieldValue = matroid.getField(column, row);
//TODO: factor must apply to pivot row value!
				uint64_t newFieldValue = galois -> add(oldFieldValue, factor);
				matroid.setField(column, row, newFieldValue);
			}
		}
	}
}

Matroid DualMatroid::transpose(Matroid& matroid) {
	int elements = matroid.getElements();
	int rank = matroid.getRank();
	int newRank = elements - rank; 
	Matroid transposed(elements, newRank);
	
	for (int newColumn = 0; newColumn < rank; newColumn++) {
		for (int newRow = 0; newRow < newRank; newRow++) {
			uint64_t newValue = matroid.getField(rank + newRow, newColumn);
			transposed.setField(newColumn, newRow, newValue);
		}
	}
	for (int newColumn = 0; newColumn < newRank; newColumn++) {
			transposed.setField(rank + newColumn, newColumn, 1);
	}	
	transposed.aliases = matroid.aliases;
	//TODO: what happens with the aliases?

	return transposed;
}
