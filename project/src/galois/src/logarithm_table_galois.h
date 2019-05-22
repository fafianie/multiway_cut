#pragma once

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
		std::vector<uint64_t> logarithmTable;
		std::vector<uint64_t> inverseLogarithmTable;
};
