#include "stdafx.h"
#include <ilcplex/ilocplex.h>
#include "multiway_cut_relaxation_solver.h"
#include "graph.h"

ILOSTLBEGIN
//using namespace std;

MultiwayCutRelaxationSolver::MultiwayCutRelaxationSolver() {
}

MultiwayCutRelaxationSolver::MultiwayCutRelaxationSolver(Graph& graph) {
	init(graph);
}

void MultiwayCutRelaxationSolver::init(Graph& graph) {
	try {
		//TODO: assume graph is normalized
		int vertices = graph.getVertices();
		vector<int> terminals;
		for (int terminal : graph.getTerminals()) {
			terminals.push_back(terminal);
		}
		
		IloModel initialModel(environment);
		model = initialModel;

		IloNumVarArray d(environment, vertices, 0.0, IloInfinity); //TODO check difference in runtime using 1.0 as upper bound
		/*for (int i = 0; i < terminals; i++)
		{
			d[termlist[i] - 1] = IloNumVar(env, 0.0, 0.0);
		}*/
		distances = d; //AVOID D?

		IloNumVarArray y(environment, vertices*terminals.size(), 0.0, IloInfinity);


		// initialize for warm start
		IloNumVarArray wd(environment);
		IloNumArray wv(environment);
		for (int vertex = 0; vertex < vertices; vertex++) {
			wd.add(d[vertex]);
			wv.add(0.0);
		}
		warmVariables = wd; //AOIVD wd and wv?
		warmValues = wv;


		// y_i,k = y[i*k-1]

		model.add(d);
		model.add(y);

		model.add(IloMinimize(environment, IloSum(d)));

		IloRangeArray constraints(environment);

		//neighbor distance constraints
		for (int u = 0; u < vertices; u++) {
			for (int v = 0; v < vertices; v++) {
				if (graph.isOutNeighbor(u, v)) {
					for (int j = 0; j < terminals.size(); j++) {
						int offset = j*vertices;
						constraints.add(y[offset + v] - y[offset + u] - d[v] <= 0);
						constraints.add(y[offset + u] - y[offset + v] - d[u] <= 0);
					}
				}
			}
		}

		//terminal distance constraints
		for (int terminalIndex = 0; terminalIndex < terminals.size(); terminalIndex++) {
			int offset = terminalIndex * vertices;
			constraints.add(y[offset + (terminals[terminalIndex])] == 0);
		}

		//terminal seperation constraints
		for (int terminalIndex = 0; terminalIndex < terminals.size(); terminalIndex++) {
			int offset = terminalIndex * vertices;
			for (int otherTerminalIndex = 0; otherTerminalIndex < terminals.size(); otherTerminalIndex++) {
				if (terminalIndex != otherTerminalIndex)	{
					constraints.add(y[offset + (terminals[otherTerminalIndex])] >= 1);
				}
			}
		}

		//ban terminals from solution
		for (int terminalIndex = 0; terminalIndex < terminals.size(); terminalIndex++) {
			constraints.add(d[(terminals[terminalIndex])] == 0);
		}

		model.add(constraints);


		IloCplex cp(model);
		cplex = cp;
		cplex.setOut(environment.getNullStream());
		cplex.setWarning(environment.getNullStream());
	}
	catch (IloException& e) {
		cerr << "Concert exception caught: " << e << endl;
	}
	catch (...) {
		cerr << "Unknown exception caught: " << endl;
	}

}

void MultiwayCutRelaxationSolver::block(int vertex) {
	IloRangeArray constraints(environment);
	constraints.add(distances[vertex] == 0);
	model.add(constraints);
	constraintStack.push(constraints);
	//cout << "ADDED CONSTRAINT " << c << endl;
	//cout << "FRONT OF Q " << constraintStack.back();
}

void MultiwayCutRelaxationSolver::select(int vertex) {
	IloRangeArray constraints(environment);
	constraints.add(distances[vertex] == 1);
	model.add(constraints);
	constraintStack.push(constraints);
	warmValues[vertex] = 1.0;
}

void MultiwayCutRelaxationSolver::pop() {
	//cout << "IS CONSTRAINT?: " << constraintStack.front() << endl;
	model.remove(constraintStack.top());
	constraintStack.pop();
}

void MultiwayCutRelaxationSolver::constraints() {
	//model.getProperties.
}


double MultiwayCutRelaxationSolver::solve() {
	try	{
		cplex.setStart(warmValues, NULL, warmVariables, NULL, NULL, NULL);
		cplex.solve();
		//cplex.
		
		//cplex.addMIPStart(warmvars, warmvals); TODO: WHAT IS THIS?
		//env.out() << "Solution status = " << cplex.getStatus() << endl;
		//env.out() << "Solution value  = " << cplex.getObjValue() << endl;
		/*IloNumArray vals(env);
		cplex.getValues(vals, dist);
		env.out() << "Values        = " << vals << endl;*/
		return cplex.getObjValue();
	}
	catch (IloException& e) {
		cerr << "Concert exception caught: " << e << endl;
		return 0;
	}
	catch (...) {
		cerr << "Unknown exception caught: " << endl;
		return 0;
	}
}

bool MultiwayCutRelaxationSolver::isZero(int vertex) { //TODO: improve performance
	IloNumArray values(environment);
	cplex.getValues(values, distances);
	return (values[vertex] == 0);
}


MultiwayCutRelaxationSolver::~MultiwayCutRelaxationSolver() {
	environment.end();
}

void MultiwayCutRelaxationSolver::addNeighbor(int vertex) {
	warmValues[vertex] = 0.5;
}

void MultiwayCutRelaxationSolver::removeNeighbor(int vertex) {
	warmValues[vertex] = 0.0;
}




// functions: initialize problem, add constraint, remove constraint (always the last one added), remove last x constraints
//
