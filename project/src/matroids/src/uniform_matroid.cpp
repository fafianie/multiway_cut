#include "stdafx.h"
#include "galois.h"
#include "matroid.h"
#include "uniform_matroid.h"


using namespace std;

Matroid UniformMatroid::generate(int elements, int rank, Galois* galois) {

	Matroid matroid(elements, rank);
	
	
	
	for (int i = 0; i < elements; i++)
	{
		uint64_t res = i+1;
		matroid.setField(i, 0, 1L);

		for (int j = 1; j < rank; j++)
		{
			matroid.setField(i, j, res);
			res = galois -> multiply(res, i+1);
		}
	}
	
	

	return matroid;

}