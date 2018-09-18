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
	uint64_t mask = pwm1[32];
	uint64_t x1x0, x2, x3;
  
	__asm__ ( 	//carry-less multiplication
		"movd %3, %%xmm1;" 
	 	"movd %4, %%xmm2;"
		"pclmulqdq $0, %%xmm1, %%xmm2;" 

		//fetch first 64 bits
		"movd %%xmm2, %0;"
                
		//fetch 32 more bits
        "psrldq $8, %%xmm2;"
        "movq %%xmm2, %%xmm3;"
        "movd %5, %%xmm1;"
        "pand %%xmm1, %%xmm3;"
        "movd %%xmm3, %1;"

		//fetch last 32 bits
        "psrldq $4, %%xmm2;"
		"movd %%xmm2, %2;"          

		: "=r" (x1x0), "=r" (x2), "=r" (x3)
		: "r" (leftOperand), "r" (rightOperand), "r" (mask)		
	);

	//modulo primitive polynomial
	uint64_t x3d = (x3 << 32) ^ (x3 >> 31) ^ (x3 >> 29) ^ (x3 >> 28) ^ x2;
	uint64_t h1h0 = (x3d << 1) ^ (x3d << 3) ^ (x3d << 4) ^ x3d;
	return h1h0 ^ x1x0;
}