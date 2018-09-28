#include "stdafx.h"
#include "naive_galois.h"
#include "powers.cpp"

static const int repetitions = 1000;
statoc const int powers = 64

bool testInverse(Galois g) {
	uint64_t operand = galois -> uniformRandomElement();
	uint64_t inverse = galois -> inverse(operand);
	uint64_t identity = galois -> multiply(inverse, operand);
	if (operand != 0 && identity != 1) {
		return false;
	}
	if (operand == 0 && identity != 0) {
		return false;
	}
	return true;
}

bool testPower(int power) {
	Galois* galois = new NaiveGalois(power);
	
		array<uint64_t, 1000> operands; //= new uint64_t[repetitions];
	
		for (int repetition = 0; repetition < repetitions; repetition++) {
			operands[repetition] = galois -> uniformRandomElement();
		}
	
		for (auto &operand : operands) {
			uint64_t inverse = galois -> inverse(operand);
			uint64_t identity = galois -> multiply(inverse, operand);
			if (operand != 0 && identity != 1) {
				succesful = false;
			}
			if (operand == 0 && identity != 0) {
				succesful = false;
			}
		}
	
		//delete operands;
		delete galois;
	

	
	}
}




int main(int argc, char* argv[]) {

	int repetitions = 1000;

	bool succesful = true;
	for (int power = 1; power < 65; power++) {
	
		Galois* galois = new NaiveGalois(power);
	
		array<uint64_t, 1000> operands; //= new uint64_t[repetitions];
	
		for (int repetition = 0; repetition < repetitions; repetition++) {
			operands[repetition] = galois -> uniformRandomElement();
		}
	
		for (auto &operand : operands) {
			uint64_t inverse = galois -> inverse(operand);
			uint64_t identity = galois -> multiply(inverse, operand);
			if (operand != 0 && identity != 1) {
				succesful = false;
			}
			if (operand == 0 && identity != 0) {
				succesful = false;
			}
		}
	
		//delete operands;
		delete galois;
	}
	
	if (succesful) {
		return 0;
	}
	return 1;
}