#include "stdafx.h"
#include "matroid.h"

using namespace std;

void changeMatroidPassedByValue(Matroid matroid) {
	for (int i = 0; i < matroid.getElements(); i++) {
		for (int j = 0; j < matroid.getRank(); j++) {
			matroid.setField(i, j, 1L);
		}
	}
}

int main(int argc, char* argv[]) {
	Matroid matroid(10, 8);
	changeMatroidPassedByValue(matroid);
	if (!matroid.allZero()) {
		return 1;
	}
	return 0;
}
