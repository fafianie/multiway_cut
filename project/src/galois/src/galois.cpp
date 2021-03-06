#include "stdafx.h"
#include "galois.h"
#include "powers.cpp"
#include "primitives.cpp"

using namespace std;

Galois::Galois(const int initW) : w(initW) {
	random_device rd;  
	randomGenerator.seed(rd());   
}

Galois::~Galois() {}

uint64_t Galois::add(uint64_t leftOperand, uint64_t rightOperand) {
	return leftOperand ^ rightOperand;
}

uint64_t Galois::inverse(uint64_t operand) {
	uint64_t square = multiply(operand, operand); 
	uint64_t result = square;
	for (int i = 0; i < (w-2); i++) {
		square = multiply(square, square);
		result = multiply(square, result);   
	}
	return result;
}

uint64_t Galois::uniformRandomElement() { 
	int bits = w;
	uint64_t result = 0;

	uniform_int_distribution<> partialDistribution(0, pwm1[16]);

	while (bits > 16) {
		result <<= 16;
		result ^= partialDistribution(randomGenerator);
		bits -= 16;
	}

	uniform_int_distribution<> remainderDistribution(0, pwm1[bits]);
	result <<= bits;
	result ^= remainderDistribution(randomGenerator);

	return result;
}

string Galois::toString(uint64_t operand) {
	bitset<64> x(operand);
	string s = x.to_string();
	return s.substr(64-w, w);
}