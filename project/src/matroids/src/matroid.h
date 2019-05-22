#pragma once

#include "stdafx.h"
#include "galois.h"

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
		std::vector<uint64_t> getElementColumn(int);
		bool isIndependent(std::vector<int>, Galois*);
		void display(Galois*);

std::vector<int> aliases; //TODO: move to private or encapsulate

	private:
		std::vector<uint64_t> representation;
		//std::vector<int> aliases;
		int elements;
		int rank;
};
