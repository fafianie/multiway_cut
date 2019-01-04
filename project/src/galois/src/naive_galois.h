#pragma once

#include "stdafx.h"
#include "galois.h"

class NaiveGalois : public Galois {
	
	public:
		NaiveGalois(const int);
		~NaiveGalois();
		
		uint64_t multiply(uint64_t, uint64_t);
		uint64_t divide(uint64_t, uint64_t);
};