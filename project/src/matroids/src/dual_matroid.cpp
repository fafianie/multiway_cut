#include "stdafx.h"
#include "graph.h"
#include "galois.h"
#include "matroid.h"
#include "dual_matroid.h"

using namespace std;

Matroid DualMatroid::generate(Matroid& inputMatroid, Galois* galois) {
	//copy the matroid first
	int numberOfElements = inputMatroid.getNumberOfElements()
	int rank = inputMatroid.getRank();
	Matroid outputMatroid(numberOfElements, rank)
	for (int column = 0; column < elements, column++) {
		for (int row = 0; row < rank; rank++) {	
			uint64_t value = inputMatroid.getField(column, row);
			outputMatroid.setField(column, row, value);
		}
	} //aliases?
	
	
	
	
	return matroid;
}

void DualMatroid::swipeDown() {
	
}

void DualMatroid::swipeUp() {
	
}

void DualMatroid::normalize() {
	
}