#pragma once

#include <ilcplex/ilocplex.h>
#include "graph.h"

class LPSolver
{
public:
	IloEnv env;
	IloModel model;
	IloCplex cplex;
	IloNumVarArray dist;
	std::stack<IloRangeArray> q;

	IloNumVarArray warmvars;
	IloNumArray warmvals;


	LPSolver();
	LPSolver(int, int, std::vector<int>, int**);
	double solve();
	bool isZero(int);
	~LPSolver();
	void block(int);
	void select(int);
	void pop();
	void init(Graph&, int, int, std::vector<int>, int**);
	void constraints();
	void addNeighbor(int);
	void remNeighbor(int);
	//void unSelect(int);


};

