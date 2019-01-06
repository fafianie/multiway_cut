#pragma once

#include "lpsolver.h"
#include "graph.h"

class MWCSolver
{
public:

	bool calc;
	double lp;
	int cur;
	int opt;
//	int bound;
	std::vector<int> opt_sol;
	std::vector<int> cur_sol;

	int nodes;
	int terminals;
	std::vector<int> termlist;
	int** adjacency;

	LPSolver lps;

	std::unordered_set<int> candidates;
	int* boundary; //-1: not neighbor to any terminal, otherwise i is neighbor to neighbors[i]
	int* status;    //-1: normal, 0: blocked, 1: picked;
	//std::unordered_set<int> cur_sol;
	//std::unordered_set<int> opt_sol;

	std::unordered_set<int>* neighborhood;

	MWCSolver(Graph&, int, int, std::vector<int>&, int**);
	~MWCSolver();
	std::vector<int> contract(int);
	void select(int);
	void undo_contract(int, std::vector<int>);
	void undo_select(int);
	int solve();
	void step(bool);

	void addCandidate(int);
	void remCandidate(int);

};

