#pragma once

#include <ilcplex/ilocplex.h>
#include "graph.h"

class MultiwayCutRelaxationSolver {
	
	public: //TODO: make more stuff private?
		LPSolver();
		LPSolver(Graph&);
		~LPSolver();
		
		double solve();
		bool isZero(int);
		void block(int);
		void select(int);
		void pop();
		void init(Graph&);
		void constraints();
		void addNeighbor(int);
		void removeNeighbor(int);

	private:
		IloEnv environment;
		IloModel model;
		IloCplex cplex;
		IloNumVarArray distances;
	
		std::stack<IloRangeArray> constraintStack;
		IloNumVarArray warmVariables;
		IloNumArray warmValues;
};

