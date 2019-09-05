#include "stdafx.h"
#include "galois.h"
#include "matroid.h"
#include "uniform_matroid.h"

using namespace std;

Matroid UniformMatroid::generate(int size, int rank, Galois* galois) {
	unordered_set<int> elements;
	for (int element = 0; element < size; element++) {
		elements.insert(element);
	}
	Matroid matroid(elements, rank);
	for (int i = 0; i < size; i++) {
		uint64_t res = i+1;
		matroid.setField(i, 0, 1L);
		for (int j = 1; j < rank; j++) {
			matroid.setField(i, j, res);
			res = galois -> multiply(res, i+1);
		}
	}
	return matroid;
}