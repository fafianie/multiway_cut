#pragma once

#include "stdafx.h"

class Matroid {
	
	public:
		Matroid(int, int);
		~Matroid();
		Matroid(const Matroid&);
	
		void swapElements(int, int);
		void setField(int, int, uint64_t);
		uint64_t getField(int, int);
		bool allZero(); //TODO: remove this method
		int getElements();
		int getRank();
		int getAlias(int);
		uint64_t* getElementColumn(int);
	
	private:
		uint64_t** representation;
		int* aliases;
		int elements;
		int rank;
};