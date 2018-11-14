#include "stdafx.h"
#include "carryless_multiplier_galois.h"
#include "matroid.h"
#include "uniform_matroid.h"

using namespace std;

int main(int argc, char* argv[]) {
	Galois* galois = new CarrylessMultiplierGalois(); //TODO: add galois to function call
	Matroid matroid = UniformMatroid::generate(10, 5, galois);
	delete galois;
	if (matroid.allZero()) { //TODO: actually check that the matroid is correct
		return 1;
	}
	return 0;
}