#pragma once

#include <ilcplex/ilocplex.h>
#include "graph.h"

class LPSolver
{
public:
	IloEnv environment;
	IloModel model;
	IloCplex cplex;
	IloNumVarArray dist;
	std::stack<IloRangeArray> constraintStack;

	IloNumVarArray warmvars;
	IloNumArray warmvals;


	LPSolver();
	LPSolver(Graph&, std::vector<int>);
	double solve();
	bool isZero(int);
	~LPSolver();
	void block(int);
	void select(int);
	void pop();
	void init(Graph&);
	void constraints();
	void addNeighbor(int);
	void removeNeighbor(int);
	//void unSelect(int);


};

