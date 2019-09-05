#include "stdafx.h"
#include "matroid.h"

using namespace std;

void changeMatroidPassedByValue(Matroid matroid) {
	for (int column : matroid.getElements()) {
		for (int row = 0; row < matroid.getRank(); row++) {
			matroid.setField(column, row, 1L);
		}
	}
}

int main(int argc, char* argv[]) {
	unordered_set<int> elements;
	for (int element = 0; element < 10; element++) {
		elements.insert(element);
	}
	Matroid matroid(elements, 8);
	changeMatroidPassedByValue(matroid);
	if (!matroid.allZero()) {
		return 1;
	}
	return 0;
}