#ifndef MULTIWAY_CUT_SRC_GALOIS_SRC_TABLE_GALOIS_H
#define MULTIWAY_CUT_SRC_GALOIS_SRC_TABLE_GALOIS_H

#include "stdafx.h"
#include "igalois.h"

class TableGalois : public IGalois
{
	public:
		TableGalois(const int w);
		~TableGalois();
		
		uint64_t multiply(uint64_t, uint64_t);
		uint64_t divide(uint64_t, uint64_t);
		
	private:
		uint64_t** multiplicationTable;
		uint64_t** divisionTable;
};

#endif