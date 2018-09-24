#include "stdafx.h"
#include "carryless_multiplier_galois.h"
#include "powers.cpp"

extern "C" {
	uint64_t pclmul(uint64_t a, uint64_t b);
	uint64_t fetch1(uint64_t mask);
	uint64_t fetch2();
}

CarrylessMultiplierGalois::CarrylessMultiplierGalois() : IGalois(64) {}

CarrylessMultiplierGalois::~CarrylessMultiplierGalois() {}

uint64_t CarrylessMultiplierGalois::divide(uint64_t leftOperand, uint64_t rightOperand) {
	if (leftOperand == 0) return 0;
	if (rightOperand == 0) return -1;
	return multiply(leftOperand, inverse(rightOperand));
}

uint64_t CarrylessMultiplierGalois::multiply(uint64_t leftOperand, uint64_t rightOperand) {
	/*uint64_t mask = pwm1[32];
	uint64_t x1x0 = pclmul(leftOperand, rightOperand);
	uint64_t x2 = fetch1(mask);
	uint64_t x3 = fetch2();
	uint64_t x3d = (x3 << 32) ^ (x3 >> 31) ^ (x3 >> 29) ^ (x3 >> 28) ^ x2;
	uint64_t h1h0 = (x3d << 1) ^ (x3d << 3) ^ (x3d << 4) ^ x3d;
	return h1h0 ^ x1x0;*/
	uint64_t mask = pwm1[32];
	uint64_t x1x0, x2, x3;
	
	//leftOperand = pwm1[32];
	//rightOperand = pwm1[32];
	/* __asm__ (
		//carry-less multiplication
		"movd %3, %%xmm0;" 
	 	"movd %4, %%xmm1;"
		"pclmulqdq $0, %%xmm0, %%xmm1;" 
		"movd %%xmm0, %0;"
 
		: "=r" (x1x0)
		: "r" (leftOperand), "r" (rightOperand)
	)*/
	/*__asm__ ( 	//carry-less multiplication
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
	);*/
	
	std::cout << " left: " << toString(leftOperand) << std::endl 
			<< "right: " << toString(rightOperand) << std::endl;
	
	
	uint64_t x2x3;
	
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
	
	x2 = x2x3 & mask;
	x3 = x2x3 >> 32;
	
	std::cout << " x1x0: " << toString(x1x0) << std::endl 
			  << " x2x3: " << toString(x2x3) << std::endl 
			  << "   x2: " << toString(x2) << std::endl 
			  << "   x3: " << toString(x3) << std::endl;
	
	/*__asm__ ( 	//carry-less multiplication
		"movd %3, %%xmm0;" 
	 	"movd %4, %%xmm1;"
		"pclmulqdq $0, %%xmm0, %%xmm1;" 

		//fetch first 64 bits
		"movd %%xmm0, %0;"
                
		//fetch 32 more bits
        "psrldq $8, %%xmm0;"
		"movd %%xmm0, %1;"

		//fetch last 32 bits
        "psrldq $4, %%xmm0;"
		"movd %%xmm0, %2;"          

		: "=r" (x1x0), "=r" (x2unmasked), "=r" (x3)
		: "r" (leftOperand), "r" (rightOperand)
	);*/
	
	//mask x2
	//uint64_t x2 = x2unmasked ^ mask;

	//modulo primitive polynomial
	uint64_t x3d = (x3 << 32) ^ (x3 >> 31) ^ (x3 >> 29) ^ (x3 >> 28) ^ x2;
	uint64_t h1h0 = (x3d << 1) ^ (x3d << 3) ^ (x3d << 4) ^ x3d;
	return h1h0 ^ x1x0;
}