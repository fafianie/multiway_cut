#ifndef MULTIWAY_CUT_SRC_GALOIS_SRC_CARRYLESS_MULTIPLIER_GALOIS_H
#define MULTIWAY_CUT_SRC_GALOIS_SRC_CARRYLESS_MULTIPLIER_GALOIS_H

#include "stdafx.h"
#include "galois.h"

class CarrylessMultiplierGalois : public Galois {
	
	public:
		CarrylessMultiplierGalois();
		~CarrylessMultiplierGalois();
		
		uint64_t multiply(uint64_t, uint64_t);
		uint64_t divide(uint64_t, uint64_t);
};

#endif