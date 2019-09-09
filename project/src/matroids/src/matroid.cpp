#include "stdafx.h"
#include "matroid.h"
#include "independent_set.h"

using namespace std;

Matroid::Matroid(unordered_set<int>& initElements, int initRank) : rank(initRank) {
	int index = 0;
	for (int element : initElements) {
		elements.insert(element);
		vector<uint64_t> columnRepresentation;
		columnRepresentation.assign(rank, 0L);
		representation.insert(make_pair(element, columnRepresentation));
		index++;
	}
}

Matroid::~Matroid() {
}

Matroid::Matroid(const Matroid& oldMatroid) : rank(oldMatroid.rank) { 
	representation = oldMatroid.representation;
	elements = oldMatroid.elements;
}

void Matroid::setField(int column, int row, uint64_t value) {
	representation[column][row] = value;
}

uint64_t Matroid::getField(int column, int row) {
	return representation[column][row];
}

unordered_set<int>& Matroid::getElements() {
	return elements;
}

int Matroid::getRank() {
	return rank;
}

vector<uint64_t>& Matroid::getElementColumn(int element) {
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

bool Matroid::isIndependent(std::vector<int>& elements, Galois* galois) {
	IndependentSet independentSet(rank, galois);
	for (const auto& element : elements) {
		vector<uint64_t>& column = getElementColumn(element);
		if (!independentSet.addColumn(column)) {
			return false;
		}
	}
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