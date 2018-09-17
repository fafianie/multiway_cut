#include "stdafx.h"
#include "galois.h"
#include "powers.cpp"

using namespace std;

/*extern "C" {
	uint64_t pclmul(uint64_t a, uint64_t b);
	uint64_t fetch1(uint64_t mask);
	uint64_t fetch2();
}

uint64_t clmul_multiply(uint64_t arg1, uint64_t arg2)
{
	uint64_t mask = pwm1[32];
	uint64_t x1x0 = pclmul(arg1, arg2);
	uint64_t x2 = fetch1(mask);
	uint64_t x3 = fetch2();
	uint64_t x3d = (x3 << 32) ^ (x3 >> 31) ^ (x3 >> 29) ^ (x3 >> 28) ^ x2;
	uint64_t h1h0 = (x3d << 1) ^ (x3d << 3) ^ (x3d << 4) ^ x3d;
	return h1h0 ^ x1x0;
}*/

int main(int argc, char* argv[])
{
	Galois galois;
	galois.set_mode_pcmul();
	uint64_t a = galois.uniform_random_element();
	uint64_t b = galois.uniform_random_element();
	galois.multiply(a, b);
	//clmul_multiply(1, 2);

	cout << "Test passed" << endl;
	return 0;
}