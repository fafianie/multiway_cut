#include "stdafx.h"
#include "carryless_multiplier_galois.h"
#include "matroid.h"
#include "uniform_matroid.h"
#include "gauss.h"
#include "powers.cpp"

using namespace std;

static const int elements = 10;
static const int matroidRank = 4;

int main(int argc, char* argv[]) {
	Galois* galois = new CarrylessMultiplierGalois();
	Matroid matroid = UniformMatroid::generate(elements, matroidRank, galois);	
	for (int i = 0; i < pw[elements]; i++) {
		vector<int> candidates;
		for (int j = 0; j < elements; j++) {
			if (i & pw[j + 1]) {
				candidates.push_back(j);
			}
		}
		bool independent = Gauss::isIndependentSet(candidates, matroidRank, matroid, galois);
		if ((candidates.size() > matroidRank) == independent) {
			return 1;
		}
	}
	delete galois;
	return 0;
}