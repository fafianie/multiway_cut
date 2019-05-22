#include "stdafx.h"
#include "table_galois.h"
#include "naive_galois.h"
#include "powers.cpp"
#include "primitives.cpp"

TableGalois::TableGalois(const int initW) : Galois(initW) {
	Galois * galois = new NaiveGalois(w);
		
	uint64_t size = pw[w];
	multiplicationTable.resize(size * size, 0L);
	divisionTable.resize(size * size, 0L);

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			int index = size * i + j;
			multiplicationTable[index] = galois -> multiply(i, j);
			divisionTable[index] = galois -> divide(i, j);
		}
	}

	delete galois;
}

TableGalois::~TableGalois() {
}
	
uint64_t TableGalois::divide(uint64_t arg1, uint64_t arg2) {
	return divisionTable[pw[w] * arg1 + arg2];
}

uint64_t TableGalois::multiply(uint64_t arg1, uint64_t arg2) {
	return multiplicationTable[pw[w] * arg1 + arg2];
}
