#include "stdafx.h"
#include "table_galois.h"
#include "naive_galois.h"

int main(int argc, char* argv[]) {

	int repetitions = 1000;

	Galois* naiveGalois = new NaiveGalois(8);
	Galois* tableGalois = new TableGalois(8);
	
	uint64_t* leftOperands = new uint64_t[repetitions];
	uint64_t* rightOperands = new uint64_t[repetitions];
	
	for (int repetition = 0; repetition < repetitions; repetition++) {
		leftOperands[repetition] = naiveGalois -> uniformRandomElement();
		rightOperands[repetition] = naiveGalois -> uniformRandomElement();
	}
	
	bool succesful = true;
	for (int repetition = 0; repetition < repetitions; repetition++) {
		uint64_t naiveMultiplication = naiveGalois -> multiply(leftOperands[repetition], rightOperands[repetition]);
		uint64_t tableMultiplication = tableGalois -> multiply(leftOperands[repetition], rightOperands[repetition]);
		uint64_t naiveDivision = naiveGalois -> divide(leftOperands[repetition], rightOperands[repetition]);
		uint64_t tableDivision = tableGalois -> divide(leftOperands[repetition], rightOperands[repetition]);
		if (naiveMultiplication != tableMultiplication) {
			succesful = false;
		}
		if (naiveDivision != tableDivision) {
			succesful = false;
		}
	}
	
	delete[] leftOperands;
	delete[] rightOperands;
	delete naiveGalois;
	delete tableGalois;
	
	if (succesful) {
		return 0;
	}
	return 1;
}