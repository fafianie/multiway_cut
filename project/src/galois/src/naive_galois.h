#ifndef MULTIWAY_CUT_SRC_GALOIS_SRC_NAIVE_GALOIS_H
#define MULTIWAY_CUT_SRC_GALOIS_SRC_NAIVE_GALOIS_H

#include "stdafx.h"
#include "igalois.h"

class NaiveGalois : public IGalois {
	
	public:
		NaiveGalois(const int w);
		~NaiveGalois();
		
		uint64_t multiply(uint64_t, uint64_t);
		uint64_t divide(uint64_t, uint64_t);
};

#endif