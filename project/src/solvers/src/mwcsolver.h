#pragma once

#include "lpsolver.h"
#include "graph.h"

class MWCSolver
{
public:

	double lp;
	int cur;
	int opt;
//	int bound;
	std::vector<int> opt_sol;
	std::vector<int> cur_sol;

	Graph* graph;

	LPSolver lps;

	std::unordered_set<int> candidates;
	std::vector<int> boundary; //-1: not neighbor to any terminal, otherwise i is neighbor to neighbors[i]
	std::vector<int> status;    //-1: normal, 0: blocked, 1: picked;
	//std::unordered_set<int> cur_sol;
	//std::unordered_set<int> opt_sol;

	//std::unordered_set<int>* neighborhood;

	MWCSolver();
	~MWCSolver();
	std::vector<int> contract(int);
	void select(int);
	void undo_contract(int, std::vector<int>);
	void undo_select(int);
	int solve(Graph&);
	void step(bool);

	void addCandidate(int);
	void removeCandidate(int);

};

