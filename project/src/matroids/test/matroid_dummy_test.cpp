#include "stdafx.h"
#include "matroid.h"

int main(int argc, char* argv[]) {
	Matroid matroid = Matroid(10, 8);
	if (!matroid.allZero()) {
		return 1;
	}
	return 0;
}