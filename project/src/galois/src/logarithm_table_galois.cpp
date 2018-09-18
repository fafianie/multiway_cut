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
	
uint64_t LogarithmTableGalois::divide(uint64_t arg1, uint64_t arg2) {
	if (arg1 == 0) {
		return 0; 
	}
	if (arg2 == 0) {
		return -1; 
	}
	uint64_t difference = logarithm(arg1) - logarithm(arg2);
	if (logarithm(arg1) < logarithm(arg2)) {
		difference += pwm1[w]; 
	}
	return inverseLogarithm(difference);
}

uint64_t LogarithmTableGalois::multiply(uint64_t arg1, uint64_t arg2) {
	if (arg1 == 0 || arg2 == 0) {
		return 0;
	}
	uint64_t sum = logarithm(arg1) + logarithm(arg2);
	if (sum >= pwm1[w]) {
		sum -= pwm1[w];
	}
	return inverseLogarithm(sum);
}

uint64_t LogarithmTableGalois::logarithm(uint64_t arg1) { 
  return logarithmTable[arg1];
}

uint64_t LogarithmTableGalois::inverseLogarithm(uint64_t arg1) {
  return inverseLogarithmTable[arg1];
}