#include "stdafx.h"
#include <ilcplex/ilocplex.h>
#include "multiway_cut_relaxation_solver.h"
#include "graph.h"

ILOSTLBEGIN

MultiwayCutRelaxationSolver::MultiwayCutRelaxationSolver() {
}

MultiwayCutRelaxationSolver::MultiwayCutRelaxationSolver(Graph& graph) {
	init(graph);
}

void MultiwayCutRelaxationSolver::init(Graph& graph) { //Graph must be normalized.
	try {
		
		unordered_set<int> vertices = graph.getVertices();
		vector<int> terminals;
		for (int terminal : graph.getTerminals()) {
			terminals.push_back(terminal);
		}
		
		IloModel initialModel(environment);
		model = initialModel;

		distances = IloNumVarArray(environment, vertices.size(), 0.0, IloInfinity); 
		IloNumVarArray y(environment, vertices.size() * terminals.size(), 0.0, IloInfinity);

		warmVariables = IloNumVarArray(environment);
		warmValues = IloNumArray(environment);
		for (int vertex : vertices) {
			warmVariables.add(distances[vertex]);
			warmValues.add(0.0);
		}
		
		model.add(distances);
		model.add(y);
		model.add(IloMinimize(environment, IloSum(distances)));

		IloRangeArray constraints(environment); //TRY EXTRACT AND USE AS PRIVATE FIELD

		//neighbor distance constraints
		for (int u : vertices) {
			for (int v : graph.getOutNeighbors(u)) {
				for (int j = 0; j < terminals.size(); j++) {
					int offset = j * vertices.size();
					constraints.add(y[offset + v] - y[offset + u] - distances[v] <= 0);
					constraints.add(y[offset + u] - y[offset + v] - distances[u] <= 0);
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
			constraints.add(distances[(terminals[terminalIndex])] == 0);
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
	IloRangeArray constraints(environment); //add directly to environment????
	constraints.add(distances[vertex] == 0);
	model.add(constraints);
	constraintStack.push(constraints);
}

void MultiwayCutRelaxationSolver::select(int vertex) {
	IloRangeArray constraints(environment);
	constraints.add(distances[vertex] == 1);
	model.add(constraints);
	constraintStack.push(constraints);
	warmValues[vertex] = 1.0;
}

void MultiwayCutRelaxationSolver::pop() {
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