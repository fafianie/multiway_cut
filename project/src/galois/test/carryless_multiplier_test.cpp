#include "stdafx.h"
#include "carryless_multiplier_galois.h"
#include "naive_galois.h"
#include "powers.cpp"

using namespace std;

int main(int argc, char* argv[]) {

	int repetitions = 1000;

	Galois* naiveGalois = new NaiveGalois(64);
	Galois* carrylessMultiplierGalois = new CarrylessMultiplierGalois();
	
	uint64_t* leftOperands = new uint64_t[repetitions];
	uint64_t* rightOperands = new uint64_t[repetitions];
	
	for (int repetition = 0; repetition < repetitions; repetition++) {
		leftOperands[repetition] = naiveGalois -> uniformRandomElement();
		rightOperands[repetition] = naiveGalois -> uniformRandomElement();
	}
	
	bool succesful = true;
	for (int repetition = 0; repetition < repetitions; repetition++) {
		uint64_t naiveMultiplication = naiveGalois -> multiply(leftOperands[repetition], rightOperands[repetition]);
		uint64_t logarithmTableMultiplication = carrylessMultiplierGalois -> multiply(leftOperands[repetition], rightOperands[repetition]);
		uint64_t naiveDivision = naiveGalois -> divide(leftOperands[repetition], rightOperands[repetition]);
		uint64_t logarithmTableDivision = carrylessMultiplierGalois -> divide(leftOperands[repetition], rightOperands[repetition]);
		if (naiveMultiplication != logarithmTableMultiplication) {
			succesful = false;
		}
		if (naiveDivision != logarithmTableDivision) {
			succesful = false;
		}
	}
	
	delete[] leftOperands;
	delete[] rightOperands;	
	delete naiveGalois;
	delete carrylessMultiplierGalois;
	
	if (succesful) {
		return 0;
	}
	return 1;
}