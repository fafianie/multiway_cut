#include "stdafx.h"
#include "matroid.h"
#include "independent_set.h"

using namespace std;

Matroid::Matroid(const int initElements, const int initRank) : elements(initElements), rank(initRank) {
//cout << "creating matroid" << endl;
	representation.assign(elements * rank, 0L);
	for (int i = 0; i < elements; i++) {
		columnToElement.push_back(i);
		elementToColumn.push_back(i);
	}
//cout << "finished creating matroid" << endl;
}

Matroid::~Matroid() {
}

Matroid::Matroid(const Matroid& oldMatroid) : elements(oldMatroid.elements), rank(oldMatroid.rank) { 
	columnToElement = oldMatroid.columnToElement;
	elementToColumn = oldMatroid.elementToColumn;
	representation = oldMatroid.representation;
}

void Matroid::setField(int column, int row, uint64_t value) {
	representation[rank * column + row] = value;
}

uint64_t Matroid::getField(int column, int row) {
	return representation[rank * column + row];
}

void Matroid::swapColumns(int leftColumn, int rightColumn) {
	for (int row = 0; row < rank; row++) {
		uint64_t leftValue = getField(leftColumn, row);
		uint64_t rightValue = getField(rightColumn, row);
		setField(leftColumn, row, rightValue);
		setField(rightColumn, row, leftValue);
	}
	cout << "swapping column << " << leftColumn << " and " << rightColumn << endl;
	int leftElement = columnToElement[leftColumn];
	int rightElement = columnToElement[rightColumn];
	columnToElement[leftColumn] = rightElement;
	elementToColumn[rightElement] = leftColumn;
	columnToElement[rightColumn] = leftElement;
	elementToColumn[leftElement] = rightColumn;
	
	
	
	
	//TODO: need better data structure
	
	// column -> element
	// element -> column
	
}

int Matroid::getElements() {
	return elements;
}

int Matroid::getRank() {
	return rank;
}

vector<uint64_t> Matroid::getElementColumn(int element) {
	vector<uint64_t> result;
	for (int row = 0; row < rank; row++) {
		result.push_back(representation[rank * elementToColumn[element] + row]);
	}
	return result;
}

bool Matroid::allZero() { //TODO: remove this method
	for (int i = 0; i < elements; i++) {
		if (elementToColumn[i] != i) {
			return false;
		}
		for (int j = 0; j < rank; j++) {
			if (representation[rank * i + j] != 0L) {
				return false;
			}
		}
	}
	return true;
}

bool Matroid::isIndependent(std::vector<int> elements, Galois* galois) {
	IndependentSet independentSet(rank, galois);
	for (const auto &element : elements) {
		vector<uint64_t> column = getElementColumn(element);
//cout << "grabbed column for element " << element << endl;
//for (int row = 0; row < rank; row++) {
//string value = galois -> toString(column[row]);
//cout << value << " ";
//}
//cout << endl;
		if (!independentSet.addColumn(column)) {
//cout << "not independent" << endl;
			return false;
		}
	}
//cout << "independent" << endl;
	return true;
}

void Matroid::display(Galois* galois) {
	for (int column = 0; column < elements; column++) {
		cout << setw(8) << columnToElement[column] << " ";
	}
	cout << endl;
	for (int row = 0; row < rank; row++) {
		for (int column = 0; column < elements; column++) {
			string value = galois -> toString(getField(column, row));
			cout << value << " ";
		}
		cout << endl;
	}
}
