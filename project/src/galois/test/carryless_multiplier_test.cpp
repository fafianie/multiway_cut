#include "stdafx.h"
#include "carryless_multiplier_galois.h"
#include "naive_galois.h"

static const int repetitions = 1000;
static const int power = 64;

int main(int argc, char* argv[]) {
	Galois *naiveGalois = new NaiveGalois(power);
	Galois *carrylessMultiplierGalois = new CarrylessMultiplierGalois();
	for (int repetition = 0; repetition < repetitions; repetition++) {
		uint64_t leftOperand = naiveGalois -> uniformRandomElement();
		uint64_t rightOperand = naiveGalois -> uniformRandomElement();
		if (naiveGalois -> multiply(leftOperand, rightOperand) != carrylessMultiplierGalois -> multiply(leftOperand, rightOperand)) {
			return 1;
		}
		if (naiveGalois -> divide(leftOperand, rightOperand) != carrylessMultiplierGalois -> divide(leftOperand, rightOperand)) {
			return 1;
		}
	}
	delete naiveGalois;
	delete carrylessMultiplierGalois;
	return 0;
}