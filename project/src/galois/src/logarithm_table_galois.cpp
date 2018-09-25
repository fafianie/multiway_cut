#include "stdafx.h"
#include "logarithm_table_galois.h"
#include "powers.cpp"
#include "primitives.cpp"

LogarithmTableGalois::LogarithmTableGalois(const int winit) : IGalois(winit) {
	int size = pw[w];
	logarithmTable = new uint64_t[size];
	inverseLogarithmTable = new uint64_t[size];

	uint64_t b = 1;

	for (int log = 0; log < (size-1); log++) {
		logarithmTable[b] = (unsigned int) log;
		inverseLogarithmTable[log] = (unsigned int) b;
		b <<= 1;
		if (b & size) {
			b ^= primpoly[w];
		}
	}
}

LogarithmTableGalois::~LogarithmTableGalois() {
	delete[] logarithmTable;
	delete[] inverseLogarithmTable;
}
	
uint64_t LogarithmTableGalois::divide(uint64_t leftOperand, uint64_t rightOperand) {
	if (leftOperand == 0) {
		return 0; 
	}
	if (rightOperand == 0) {
		return -1; 
	}
	uint64_t difference = logarithm(leftOperand) - logarithm(rightOperand);
	if (logarithm(leftOperand) < logarithm(rightOperand)) {
		difference += pwm1[w]; 
	}
	return inverseLogarithm(difference);
}

uint64_t LogarithmTableGalois::multiply(uint64_t leftOperand, uint64_t rightOperand) {
	if (leftOperand == 0 || rightOperand == 0) {
		return 0;
	}
	uint64_t sum = logarithm(leftOperand) + logarithm(rightOperand);
	if (sum >= pwm1[w]) {
		sum -= pwm1[w];
	}
	return inverseLogarithm(sum);
}

uint64_t LogarithmTableGalois::logarithm(uint64_t leftOperand) { 
  return logarithmTable[leftOperand];
}

uint64_t LogarithmTableGalois::inverseLogarithm(uint64_t leftOperand) {
  return inverseLogarithmTable[leftOperand];
}