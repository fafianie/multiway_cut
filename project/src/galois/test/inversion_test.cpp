#include "stdafx.h"
#include "naive_galois.h"

static const int repetitions = 1000;
static const int powers = 64;

bool testPower(int power) {
	Galois *galois = new NaiveGalois(power);
	for (int repetition = 0; repetition < repetitions; repetition++) {
		uint64_t operand = galois -> uniformRandomElement();
		uint64_t inverse = galois -> inverse(operand);
		uint64_t identity = galois -> multiply(inverse, operand);
		if (operand != 0 && identity != 1) {
			return false;
		}
		if (operand == 0 && identity != 0) {
			return false;
		}
	}
	delete galois;
	return true;
}

int main(int argc, char* argv[]) {
	for (int power = 1; power <= powers; power++) {
		if(!testPower(power)) {
			return 1;
		}
	}
	return 0;
}