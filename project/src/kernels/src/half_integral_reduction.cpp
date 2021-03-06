#include "stdafx.h"
#include "half_integral_reduction.h"
#include "multiway_cut_relaxation_solver.h"
#include "graph.h"

using namespace std;

void HalfIntegralReduction::reduce(Graph& inputGraph) {
	
	MultiwayCutRelaxationSolver relaxationSolver;
	relaxationSolver.init(inputGraph);
	relaxationSolver.solve();
	
	unordered_set<int> candidates;
	unordered_set<int> considered;
	for (int terminal : inputGraph.getTerminals()) {
		for (int neighbor : inputGraph.getInNeighbors(terminal)) {
			candidates.insert(neighbor);
		}
	}
	
	while (!candidates.empty()) {
		int candidate = *candidates.begin();
		if (considered.find(candidate) == considered.end()) {
			candidates.erase(candidate);
			continue;
		}
		considered.insert(candidate);
		if (inputGraph.isTerminal(candidate)) {
			continue;
		}
		if (!relaxationSolver.isZero(candidate)) {
			continue;
		}
		for (int newCandidate : inputGraph.getInNeighbors(candidate)) {
			candidates.insert(newCandidate);
		}
		inputGraph.contract(candidate);
		candidates.erase(candidate);
		//ensure we don't revisit and get stuck in a loop (should not happen because we either contract or terminate on border
	}
}




