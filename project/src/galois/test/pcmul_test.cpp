#include "stdafx.h"
#include "galois.h"

using namespace std;

int main(int argc, char* argv[])
{
	Galois galois;
	galois.set_mode_pcmul();
	uint64_t a = galois.uniform_random_element();
	uint64_t b = galois.uniform_random_element();
	galois.multiply(a, b);

	cout << "Test passed" << endl;
	return 0;
}