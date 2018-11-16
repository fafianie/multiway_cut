#include "stdafx.h"
#include "carryless_multiplier_galois.h"
#include "matroid.h"
#include "gauss.h"
#include "transversal_matroid.h"

using namespace std;

int main(int argc, char* argv[]) {
	Galois* galois = new CarrylessMultiplierGalois();
	Graph graph(10);
	Matroid matroid = TransversalMatroid::generate(graph, galois);
	delete galois;
	return 0;
}