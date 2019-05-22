#pragma once

#include "stdafx.h"
#include "galois.h"

class TableGalois : public Galois {
	
	public:
		TableGalois(const int w);
		~TableGalois();
		
		uint64_t multiply(uint64_t, uint64_t);
		uint64_t divide(uint64_t, uint64_t);
		
	private:
		std::vector<uint64_t> multiplicationTable;
		std::vector<uint64_t> divisionTable;
};
