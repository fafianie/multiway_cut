#include "stdafx.h"
#include "naive_galois.h"
#include "powers.cpp"
#include "primitives.cpp"

NaiveGalois::NaiveGalois(const int winit) : IGalois(winit) {}

NaiveGalois::~NaiveGalois() {}

uint64_t NaiveGalois::divide(uint64_t arg1, uint64_t arg2)
{
	if (arg1 == 0) return 0;
	if (arg2 == 0) return -1;
	return multiply(arg1, inverse(arg2));
}

uint64_t NaiveGalois::multiply(uint64_t arg1, uint64_t arg2)
{
	uint64_t a = arg1;
	uint64_t b = arg2;
	uint64_t p = 0;

	for (int i = 0; i < w; i++)
	{
		if (b & 1)
		{
			p ^= a; 
		}
		b >>= 1;

		bool carry = false;
		if (a & (pw[w-1]))
		{
			carry = true;
		}
		a <<= 1;

		if (carry)
		{
			a ^= (primpoly[w]);
		}
	}

	return p;
}