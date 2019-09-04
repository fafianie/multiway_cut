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
		unordered_set<int> vertices = graph.getVertices();
		vector<int> terminals;
		for (int terminal : graph.getTerminals()) {
			terminals.push_back(terminal);
		}
		
		IloModel initialModel(environment);
		model = initialModel;

		distances = IloNumVarArray(environment, vertices.size(), 0.0, IloInfinity); //TODO check difference in runtime using 1.0 as upper bound
		/*for (int i = 0; i < terminals; i++)
		{
			d[termlist[i] - 1] = IloNumVar(env, 0.0, 0.0);
		}*/

		IloNumVarArray y(environment, vertices.size() * terminals.size(), 0.0, IloInfinity);


		// initialize for warm start
		//IloNumVarArray wd(environment);
		//IloNumArray wv(environment);
		//for (int vertex : vertices) {
		//	wd.add(d[vertex]);
		//	wv.add(0.0);
		//}
		//warmVariables = wd; //AOIVD wd and wv?
		//warmValues = wv;
		warmVariables = IloNumVarArray(environment);
		warmValues = IloNumArray(environment);
		for (int vertex : vertices) {
			warmVariables.add(distances[vertex]);
			warmValues.add(0.0);
		}
		

		// y_i,k = y[i*k-1]

		model.add(distances);
		model.add(y);

		model.add(IloMinimize(environment, IloSum(distances)));

		IloRangeArray constraints(environment);

		//neighbor distance constraints
		for (int u : vertices) {
			for (int v : vertices) {
				if (graph.isOutNeighbor(u, v)) {
					for (int j = 0; j < terminals.size(); j++) {
						int offset = j * vertices.size();
						constraints.add(y[offset + v] - y[offset + u] - distances[v] <= 0);
						constraints.add(y[offset + u] - y[offset + v] - distances[u] <= 0);
					}
				}
			}
		}

		//terminal distance constraints
		for (int terminalIndex = 0; terminalIndex < terminals.size(); terminalIndex++) {
			int offset = terminalIndex * vertices.size();
			constraints.add(y[offset + (terminals[terminalIndex])] == 0);
		}

		//terminal seperation constraints
		for (int terminalIndex = 0; terminalIndex < terminals.size(); terminalIndex++) {
			int offset = terminalIndex * vertices.size();
			for (int otherTerminalIndex = 0; otherTerminalIndex < terminals.size(); otherTerminalIndex++) {
				if (terminalIndex != otherTerminalIndex) {
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
