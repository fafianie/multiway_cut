#include "stdafx.h"
#include "carryless_multiplier_galois.h"
#include "powers.cpp"

using namespace std;

int main(int argc, char* argv[]) {
	IGalois *galois = new CarrylessMultiplierGalois();
	uint64_t a = galois -> uniformRandomElement();
	uint64_t b = galois -> uniformRandomElement();
	uint64_t result = galois -> multiply(a, b);

	if (result != 0) {
		return 0;
	}
	return 1;
}