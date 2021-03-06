#pragma once

#include "multiway_cut_relaxation_solver.h"
#include "graph.h"

class MultiwayCutSolver {
	public:
	
		MultiwayCutSolver();
		~MultiwayCutSolver();
		int solve(Graph&);
		int getLeaves();

	private:
		void printCandidates();//TODO: remove
		std::vector<int> contract(int);
		void select(int);
		void undoContract(int, std::vector<int>&);
		void undoSelect(int);
		void step();
		void addCandidate(int);
		void removeCandidate(int);

		double lp;
		int cur;
		int opt;
		std::vector<int> optimalSolution;
		std::vector<int> currentSolution;
		Graph* graph;
		MultiwayCutRelaxationSolver relaxationSolver;
		std::unordered_set<int> candidates;
		std::vector<int> boundary;  //-1: not neighbor to any terminal, otherwise i is neighbor to neighbors[i]
		std::vector<int> status;    //-1: normal, 0: blocked, 1: picked;
		int leaves = 0;
};