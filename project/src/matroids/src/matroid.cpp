#include "stdafx.h"
#include "matroid.h"

using namespace std;

Matroid::Matroid(const int initElements, const int initRank) : elements(initElements), rank(initRank) {
	
	representation = new uint64_t*[elements];
	aliases = new int[rank];
	      
	for (int i = 0; i < elements; i++) {
		aliases[i] = 0;
		representation[i] = new uint64_t[rank]; //TODO: CHECK IF THESE ARE ACTUALLY ZERO
	}
}

Matroid::~Matroid() {

	for (int i = 0; i < elements; i++) {
		delete[] representation[i];
	}
	delete[] aliases;
}

bool Matroid::allZero() { //TODO: remove this method
	for (int i = 0; i < elements; i++) {
		if (aliases[i] != 0) {
			std::cout << "aliases[" << i << "] = " << aliases[i] << std::endl;
			return false;
		}
		for (int j = 0; j < rank; j++) {
			if (representation[i][j] != 0L) {
				std::cout << "representation[" << i << "][" << j << "] = " << representation[i][j] << std::endl;
				return false;
			}
		}
	}
	return true;
}