#include "stdafx.h"
#include "matroid.h"

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
	for (int i = 0; i < elements; i++) {
		cout << aliases[i] << endl;
	}
	delete[] aliases;
}

void Matroid::setField(int column, int row, uint64_t value) {
	representation[column][row] = value;
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