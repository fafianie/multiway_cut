#include "stdafx.h"
#include "matroid.h"
#include "independent_set.h"

using namespace std;

Matroid::Matroid(const int initElements, const int initRank) : elements(initElements), rank(initRank) {
	representation = new uint64_t*[elements];
	aliases = new int[elements];
	      
	for (int i = 0; i < elements; i++) {
		aliases[i] = i;
		representation[i] = new uint64_t[rank]; 
		for (int j = 0; j < rank; j++) {
			representation[i][j] = 0L;
		}
	}
}

Matroid::~Matroid() {
	for (int i = 0; i < elements; i++) {
		delete[] representation[i];
	}
	delete[] representation;
	delete[] aliases;
}

Matroid::Matroid(const Matroid& oldMatroid) : elements(oldMatroid.elements), rank(oldMatroid.rank) { 
	representation = new uint64_t*[elements];
	aliases = new int[elements];

	for (int i = 0; i < elements; i++) {
		aliases[i] = oldMatroid.aliases[i];
		representation[i] = new uint64_t[rank];
		for (int j = 0; j < rank; j++) {
			representation[i][j] = oldMatroid.representation[i][j];
		}
	}
}

void Matroid::setField(int column, int row, uint64_t value) {
	representation[aliases[column]][row] = value;
}

uint64_t Matroid::getField(int column, int row) {
	return representation[aliases[column]][row];
}

void Matroid::swapElements(int leftElement, int rightElement) {
	int leftAlias = aliases[leftElement];
	int rightAlias = aliases[rightElement];
	aliases[leftElement] = rightAlias;
	aliases[rightElement] = leftAlias;
}

int Matroid::getElements() {
	return elements;
}

int Matroid::getRank() {
	return rank;
}

int Matroid::getAlias(int element) {
	return aliases[element];
}

uint64_t* Matroid::getElementColumn(int element) {
	return representation[aliases[element]];
}

bool Matroid::allZero() { //TODO: remove this method
	for (int i = 0; i < elements; i++) {
		if (aliases[i] != i) {
			return false;
		}
		for (int j = 0; j < rank; j++) {
			if (representation[i][j] != 0L) {
				return false;
			}
		}
	}
	return true;
}

bool Matroid::isIndependent(std::vector<int> elements, Galois* galois) {
	IndependentSet independentSet(rank, galois);
	for (const auto &element : elements) {
		uint64_t* column = representation[aliases[element]];
		if (!independentSet.addColumn(column)) {
			return false;
		}
	}
	return true;
}

void Matroid::display(Galois* galois) {
	for (int row = 0; row < rank; row++) {
		for (int column = 0; column < elements; column++) {
			string value = galois -> toString(getField(column, row));
			cout << value << " ";
		}
		cout << endl;
	}
}