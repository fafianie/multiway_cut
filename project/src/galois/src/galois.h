#ifndef MULTIWAY_CUT_SRC_GALOIS_SRC_GALOIS_H
#define MULTIWAY_CUT_SRC_GALOIS_SRC_GALOIS_H

#include "stdafx.h"

class Galois {
	
	public:
		Galois(const int);
		virtual ~Galois();
		
		uint64_t add(uint64_t, uint64_t);
		virtual uint64_t multiply(uint64_t, uint64_t) = 0;
		virtual uint64_t divide(uint64_t, uint64_t) = 0;
		uint64_t inverse(uint64_t); 
		uint64_t uniformRandomElement();
		std::string toString(uint64_t);
		
	protected:
		std::mt19937 randomGenerator;
		int w;
};

#endif