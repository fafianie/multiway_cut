#include "stdafx.h"
#include "table_galois.h"
#include "naive_galois.h"

static const int repetitions = 1000;
static const int powers = 8;

bool testPower(int power) {
	Galois *naiveGalois = new NaiveGalois(power);
	Galois *tableGalois = new TableGalois(power);
	for (int repetition = 0; repetition < repetitions; repetition++) {
		uint64_t leftOperand = naiveGalois -> uniformRandomElement();
		uint64_t rightOperand = naiveGalois -> uniformRandomElement();
		if (naiveGalois -> multiply(leftOperand, rightOperand) != tableGalois -> multiply(leftOperand, rightOperand)) {
			return false;
		}
		if (naiveGalois -> divide(leftOperand, rightOperand) != tableGalois -> divide(leftOperand, rightOperand)) {
			return false;
		}
	}
	delete naiveGalois;
	delete tableGalois;
	return true;
}

int main(int argc, char* argv[]) {
	for (int power = 1; power <= powers; power++) {
		if (!testPower(power)) {
			return 1;
		}
	}
	return 0;
}