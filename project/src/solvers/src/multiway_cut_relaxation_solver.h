#pragma once

#include <ilcplex/ilocplex.h>
#include "graph.h"

class MultiwayCutRelaxationSolver {
	
	public:
		MultiwayCutRelaxationSolver();
		MultiwayCutRelaxationSolver(Graph&);
		~MultiwayCutRelaxationSolver();
		
		double solve();
		bool isZero(int);
		void block(int);
		void select(int);
		void pop();
		void init(Graph&);
		//void constraints();
		void addNeighbor(int);
		void removeNeighbor(int);

	private:
		IloEnv environment;
		IloModel model;
		IloCplex cplex;
		IloNumVarArray distances;
		//IloRangeArray constraints;
		
		std::stack<IloRangeArray> constraintStack;
		IloNumVarArray warmVariables;
		IloNumArray warmValues;
};