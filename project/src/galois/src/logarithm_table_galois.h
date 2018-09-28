#ifndef MULTIWAY_CUT_SRC_GALOIS_SRC_LOGARITHM_TABLE_GALOIS_H
#define MULTIWAY_CUT_SRC_GALOIS_SRC_LOGARITHM_TABLE_GALOIS_H

#include "stdafx.h"
#include "galois.h"

class LogarithmTableGalois : public Galois {
	
	public:
		LogarithmTableGalois(const int w);
		~LogarithmTableGalois();
		
		uint64_t multiply(uint64_t, uint64_t);
		uint64_t divide(uint64_t, uint64_t);
		uint64_t logarithm(uint64_t); 
		uint64_t inverseLogarithm(uint64_t); 
		
	private:
		uint64_t*  logarithmTable;
		uint64_t*  inverseLogarithmTable;
};

#endif