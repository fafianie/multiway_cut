#include "stdafx.h"
#include "carryless_multiplier_galois.h"
#include "matroid.h"
#include "powers.cpp"
#include "uniform_matroid.h"
#include "independent_set.h"

using namespace std;

static const int elements = 10;
static const int matroidRank = 4;

int main(int argc, char* argv[]) {
	Galois* galois = new CarrylessMultiplierGalois();
	Matroid matroid = UniformMatroid::generate(elements, matroidRank, galois);	
	for (int candidateSeed = 0; candidateSeed < pw[elements]; candidateSeed++) {
		vector<int> candidates;
		for (int elementIndex = 0; elementIndex < elements; elementIndex++) {
			if (candidateSeed & pw[elementIndex + 1]) {
				candidates.push_back(elementIndex);
			}
		}
		bool independent = matroid.isIndependent(candidates, galois);
		if ((candidates.size() > matroidRank) == independent) {
			return 1;
		}
	}
	delete galois;
	return 0;
}