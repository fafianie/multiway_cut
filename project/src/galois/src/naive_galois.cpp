#include "stdafx.h"
#include "naive_galois.h"
#include "powers.cpp"
#include "primitives.cpp"

NaiveGalois::NaiveGalois(const int initW) : Galois(initW) {}

NaiveGalois::~NaiveGalois() {}

uint64_t NaiveGalois::divide(uint64_t leftOperand, uint64_t rightOperand) {
	if (leftOperand == 0) return 0;
	if (rightOperand == 0) return -1;
	return multiply(leftOperand, inverse(rightOperand));
}

uint64_t NaiveGalois::multiply(uint64_t leftOperand, uint64_t rightOperand) {
	uint64_t a = leftOperand;
	uint64_t b = rightOperand;
	uint64_t p = 0;

	for (int i = 0; i < w; i++)	{
		if (b & 1) {
			p ^= a; 
		}
		b >>= 1;

		bool carry = false;
		if (a & (pw[w-1])) {
			carry = true;
		}
		a <<= 1;

		if (carry) {
			a ^= (primpoly[w]);
		}
	}

	return p;
}