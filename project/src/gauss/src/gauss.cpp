#include "stdafx.h"
#include "galois.h"
#include "gauss.h"
#include "matroid.h"

using namespace std;

bool Gauss::isIndependentSet(vector<int>& elements, 
							 int rows, 
							 Matroid matroid, 
							 Galois* galois) {
	if (rows < elements.size()) {
		return false;
	}
	
	for (int elementIndex = 0; elementIndex < elements.size(); elementIndex++) {
		
		//can give up if a column is zero...
		//so in this case we don't have to pivot at all
		
	
	
	}
	
	
	
	
	
	
	return true;
}

void Gauss::swapRows(int element, 
					 int otherElement, 
					 int startingRow,
					 int rows,
					 Matroid& matroid) {
	for (int row = startingRow; row < rows; row++) {
		uint64_t oldValue = matroid.getField(element, row);
		uint64_t otherOldValue = matroid.getField(otherElement, row);
		matroid.setField(element, row, otherOldValue);
		matroid.setField(otherElement, row, oldValue);
	}
	matroid.swapElements(element, otherElement);
}
