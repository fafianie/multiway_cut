#pragma once

#include "stdafx.h"

class Matroid {
	
	public:
		Matroid(int, int);
		~Matroid();
	
		void swapElements(int, int);
		bool allZero(); //TODO: remove this method
	
	private:
		uint64_t **representation;
		int *aliases;
		int elements;
		int rank;
};