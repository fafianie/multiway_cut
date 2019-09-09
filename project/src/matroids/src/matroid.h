#pragma once

#include "stdafx.h"
#include "galois.h"

class Matroid {
	
	public:
		Matroid(std::unordered_set<int>&, int);
		Matroid(int, int);
		~Matroid();
		Matroid(const Matroid&);
	
		void setField(int, int, uint64_t);
		uint64_t getField(int, int);
		bool allZero();
		std::unordered_set<int>& getElements();
		int getRank();
		std::vector<uint64_t>& getElementColumn(int);
		bool isIndependent(std::vector<int>&, Galois*);
		void display(Galois*);
		void display(std::vector<int>&, Galois*);


	private:
		std::unordered_map<int, std::vector<uint64_t>> representation;
		std::unordered_set<int> elements;
		int rank;
};