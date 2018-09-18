#include "stdafx.h"
#include "table_galois.h"
#include "naive_galois.h"
#include "powers.cpp"
#include "primitives.cpp"

TableGalois::TableGalois(const int winit) : IGalois(winit) 
{
	IGalois * galois = new NaiveGalois(w);
		
	uint64_t size = pw[w];
	multiplicationTable = new uint64_t*[size];
	divisionTable = new uint64_t*[size];
      
	for (int i = 0; i < size; i++)
	{
		multiplicationTable[i] = new uint64_t[size];
		divisionTable[i] = new uint64_t[size];
		for (int j = 0; j < size; j++)
		{
			multiplicationTable[i][j] = galois -> multiply(i, j);
			divisionTable[i][j] = galois -> divide(i, j);
		}
	}

	delete galois;
}

TableGalois::~TableGalois() 
{
	uint64_t size = pw[w];
	for (int i = 0; i < size; i++) 
	{
		delete[] divisionTable[i];
		delete[] multiplicationTable[i];
	}
	
	delete[] divisionTable;
	delete[] multiplicationTable;
}
	
uint64_t TableGalois::divide(uint64_t arg1, uint64_t arg2)
{
	return divisionTable[arg1][arg2];
}

uint64_t TableGalois::multiply(uint64_t arg1, uint64_t arg2)
{
	return multiplicationTable[arg1][arg2];
}