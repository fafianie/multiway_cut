#include "stdafx.h"
#include "igalois.h"
#include "powers.cpp"
#include "primitives.cpp"

using namespace std;

IGalois::IGalois(const int winit) : w(winit) {
	random_device rd;  
	randomGenerator.seed(rd());   
}

IGalois::~IGalois() {}

uint64_t IGalois::add(uint64_t leftOperand, uint64_t rightOperand) {
	return leftOperand ^ rightOperand;
}

uint64_t IGalois::inverse(uint64_t operand) {
	//TODO:fix for small w?? CHECK IF TEST WORKS
	uint64_t square = multiply(operand, operand); 
	uint64_t result = square;
	for (int i = 0; i < (w-2); i++) {
		square = multiply(square, square);
		result = multiply(square, result);   
	}
	return result;
}

uint64_t IGalois::uniformRandomElement() { 
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

string IGalois::toString(uint64_t operand) {
	std::bitset<64> x(operand);
	string s = x.to_string();
	return s.substr(64-w, w);
}