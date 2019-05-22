#include "stdafx.h"
#include "carryless_multiplier_galois.h"
#include "naive_galois.h"
#include "matroid.h"
#include "powers.cpp"
#include "uniform_matroid.h"
#include "independent_set.h"

using namespace std;

static const int elements = 10;
static const int matroidRank = 4;

int main(int argc, char* argv[]) {
cout << "starting test" << endl;
	Galois* galois = new NaiveGalois(16);
	Matroid matroid = UniformMatroid::generate(elements, matroidRank, galois);	
cout << "generated matroid" << endl;
matroid.display(galois);
	for (int candidateSeed = 0; candidateSeed < pw[elements]; candidateSeed++) {
cout << "testing seed " << candidateSeed << endl;
		vector<int> candidates;
		for (int elementIndex = 0; elementIndex < elements; elementIndex++) {
			if (candidateSeed & pw[elementIndex + 1]) {
				candidates.push_back(elementIndex);
			}
		}
cout << "done seeding" << endl;
		bool independent = matroid.isIndependent(candidates, galois);
cout << "number of candidates = " << candidates.size() << endl;
cout << "independent = " << independent << endl;
		if ((candidates.size() > matroidRank) == independent) {
cout << "before failing" << endl;
			return 1;
		}
cout << "done testing seed " << candidateSeed << endl;
	}
cout << "before succeeding" << endl;
	delete galois;
	return 0;
}
