#include "stdafx.h"
#include "matroid.h"
#include "independent_set.h"

using namespace std;

Matroid::Matroid(unordered_set<int>& initElements, int initRank) : rank(initRank) {
//cout << "creating matroid" << endl;
	//representation.assign(elements * rank, 0L);
	int index = 0;
	for (int element : initElements) {
		elements.insert(element);
		//columnToElement.push_back(element);
		//elementToColumn.push_back(index);
		vector<uint64_t> columnRepresentation;
		columnRepresentation.assign(rank, 0L);
		representation.insert(make_pair(element, columnRepresentation));
		index++;
	}
//cout << "finished creating matroid" << endl;
}

Matroid::~Matroid() {
}

Matroid::Matroid(const Matroid& oldMatroid) : rank(oldMatroid.rank) { 
	//columnToElement = oldMatroid.columnToElement;
	//elementToColumn = oldMatroid.elementToColumn;
	representation = oldMatroid.representation;
}

void Matroid::setField(int column, int row, uint64_t value) {
	representation[column][row] = value;
}

uint64_t Matroid::getField(int column, int row) {
	return representation[column][row];
}

/*void Matroid::swapColumns(int leftColumn, int rightColumn) { //TODO: make obsolete
	//TODO: why do we need to swap at all if we have references to columns and can handle whatever...
	for (int row = 0; row < rank; row++) {
		uint64_t leftValue = getField(leftColumn, row);
		uint64_t rightValue = getField(rightColumn, row);
		setField(leftColumn, row, rightValue);
		setField(rightColumn, row, leftValue);
	}
	int leftElement = columnToElement[leftColumn];
	int rightElement = columnToElement[rightColumn];
	columnToElement[leftColumn] = rightElement;
	elementToColumn[rightElement] = leftColumn;
	columnToElement[rightColumn] = leftElement;
	elementToColumn[leftElement] = rightColumn;
}*/

unordered_set<int>& Matroid::getElements() {
	return elements;
}

int Matroid::getRank() {
	return rank;
}

vector<uint64_t> Matroid::getElementColumn(int element) {
	return representation[element];
}

bool Matroid::allZero() {
	for (const auto& entry : representation) {
		for (uint64_t field : entry.second) {
			if (field != 0L) {
				return false;
			}
		}
	}
	return true;
}

//TODO: PASS BY REFERENCE< CHECK EVERYWHERE>
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

void Matroid::display(vector<int>& orderedElements, Galois* galois) {
	for (int element : orderedElements) {
		cout << setw(8) << element << " ";
	}
	cout << endl;
	for (int row = 0; row < rank; row++) {
		for (int column : elements) {
			string value = galois -> toString(getField(column, row));
			cout << value << " ";
		}
		cout << endl;
	}
}

void Matroid::display(Galois* galois) {
	vector<int> orderedElements;
	for (int element : elements) {
		orderedElements.push_back(element);
	}
	sort(orderedElements.begin(), orderedElements.end());
	display(orderedElements, galois);
}



