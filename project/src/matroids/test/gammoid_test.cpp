#include "stdafx.h"
#include "carryless_multiplier_galois.h"
#include "naive_galois.h"
#include "matroid.h"
#include "gauss.h"
#include "dual_matroid.h"

using namespace std;

int main(int argc, char* argv[]) {
	Galois* galois = new NaiveGalois(8);
	
	Matroid matroid(12, 8);
	
	for (int column = 0; column < matroid.getElements(); column++) {
		for (int row = 0; row < matroid.getRank(); row++) {
			bool zero = true;
			while (zero) {
				uint64_t value = galois -> uniformRandomElement();
				if (value != 0L) {
					matroid.setField(column, row, value);
					zero = false;
				}
			}
		}
	}

	Matroid dualMatroid = DualMatroid::generate(matroid, galois);

	delete galois;
	return 0;
}