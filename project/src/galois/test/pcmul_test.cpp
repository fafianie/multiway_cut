#include "stdafx.h"
#include "carryless_multiplier_galois.h"
#include "naive_galois.h"
#include "powers.cpp"

using namespace std;

int main(int argc, char* argv[]) {
	IGalois *carrylessMultiplierGalois = new CarrylessMultiplierGalois();
	uint64_t a = carrylessMultiplierGalois -> uniformRandomElement();
	uint64_t b = carrylessMultiplierGalois -> uniformRandomElement();
	uint64_t carryless = carrylessMultiplierGalois -> multiply(a, b);
	
	IGalois *naiveGalois = new NaiveGalois(64);
	uint64_t naive = naiveGalois -> multiply(a, b);

	std::cout << carryless << endl << naive << endl;
	
	if (carryless == naive) {
		return 0;
	}
	return 1;
}