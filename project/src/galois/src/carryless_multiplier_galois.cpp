#include "stdafx.h"
#include "carryless_multiplier_galois.h"
#include "powers.cpp"

CarrylessMultiplierGalois::CarrylessMultiplierGalois() : IGalois(64) {}

CarrylessMultiplierGalois::~CarrylessMultiplierGalois() {}

uint64_t CarrylessMultiplierGalois::divide(uint64_t leftOperand, uint64_t rightOperand) {
	if (leftOperand == 0) return 0;
	if (rightOperand == 0) return -1;
	return multiply(leftOperand, inverse(rightOperand));
}

uint64_t CarrylessMultiplierGalois::multiply(uint64_t leftOperand, uint64_t rightOperand) {
	uint64_t x1x0, x2x3;
	
	__asm__ (
		"movd %2, %%xmm0;" 
	 	"movd %3, %%xmm1;"
		"pclmulqdq $0, %%xmm0, %%xmm1;" 
		"movd %%xmm1, %0;"
		
		"psrldq $8, %%xmm1;"
		"movd %%xmm1, %1;"
	
		: "=r" (x1x0), "=r" (x2x3)
		: "r" (leftOperand), "r" (rightOperand)
	);
	
	uint64_t x2 = x2x3 & pwm1[32];
	uint64_t x3 = x2x3 >> 32;
	uint64_t x3d = (x3 << 32) ^ (x3 >> 31) ^ (x3 >> 29) ^ (x3 >> 28) ^ x2;
	uint64_t h1h0 = (x3d << 1) ^ (x3d << 3) ^ (x3d << 4) ^ x3d;
	return h1h0 ^ x1x0;
}