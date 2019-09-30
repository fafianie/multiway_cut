#include "stdafx.h"
#include <ilcplex/ilocplex.h>
#include "multiway_cut_solver.h"
#include "multiway_cut_relaxation_solver.h"
#include "graph.h"

using namespace std;

MultiwayCutSolver::MultiwayCutSolver() {
}


MultiwayCutSolver::~MultiwayCutSolver(){ 
}

int MultiwayCutSolver::solve(Graph& inputGraph) { //Graph must be normalized.
	graph = &inputGraph;
	unordered_set<int> vertices = graph -> getVertices();
	vector<int> terminals;
	//TODO: do we really need a vector?
	for (int terminal : graph -> getTerminals()) {
		terminals.push_back(terminal);
	}
	
	relaxationSolver.init(*graph);

	boundary.assign(vertices.size(), -1);
	status.assign(vertices.size(), -1);

	for (auto terminal : terminals) {
		status[terminal] = 0;
		cout << "TERMINAL " << terminal << " with neighborhood";
		for (auto neighbor : graph -> getOutNeighbors(terminal)) {
			cout << " " << neighbor;
		}
		cout << endl;
	}

	cur = 0; //TODO: rename?
	opt = 0;

	//check feasibility and set up neighborhoods
	for (int terminal : terminals)	{
		for (int otherTerminal : terminals)	{
			if (graph -> isOutNeighbor(terminal, otherTerminal)) {
				//infeasible
				return -1;
			}
		}
		
		for (int neighbor : graph -> getOutNeighbors(terminal)) {
			if (boundary[neighbor] == -1) {
				boundary[neighbor] = terminal;
				candidates.insert(neighbor);
				continue;
			}
			if (status[neighbor] == -1) {
				select(neighbor);
			}
		}
	}

	//establish bound
	opt = static_cast<int> (2 * relaxationSolver.solve()); //assume k is not known
	step();

	//verify correctness
	MultiwayCutRelaxationSolver lps2;
	lps2.init(*graph);

	for (auto v : optimalSolution) {
		lps2.select(v);
	}

	return opt;
}

void MultiwayCutSolver::step() {
	lp = relaxationSolver.solve();
	if (lp == cur) {
		if (opt > cur) {
			opt = cur;
			optimalSolution.clear();
			optimalSolution.insert(optimalSolution.begin(), currentSolution.begin(), currentSolution.end());
		}
		leaves++;
		return;
	}
	if (lp >= opt) { 
		leaves++;
		return;
	}
	
	bool easy = false;
	vector<int> easyContractions;

	for (auto candidate : candidates) {
		if (relaxationSolver.isZero(candidate)) {
			easy = true;
			easyContractions.push_back(candidate);	
		}
	}
	
	if (easy) {
		vector<vector<int>> allActions;
		for (auto candidate : easyContractions) {		
			vector<int> actions = contract(candidate);
			allActions.push_back(actions);
		}
		step();
		for (int i = easyContractions.size() - 1; i > -1; i--) {
			undoContract(easyContractions[i], allActions[i]);
		}
		return;
	}

	vector<int> candidatesCopy;
	for (auto candidate : candidates) {
		candidatesCopy.push_back(candidate);
	}

	for (auto const& candidate : candidatesCopy) {	
		vector<int> actions = contract(candidate);
		double lp0 = relaxationSolver.solve();
		if (lp0 == lp) {
			step();
			undoContract(candidate, actions);
			return;
		}
		undoContract(candidate, actions);
	} 

	//branch on arbitrary candidate
	if (candidates.size() > 0) {
		int candidate = *candidates.begin();

		select(candidate);
		step();
		undoSelect(candidate);

		vector<int> actions = contract(candidate);
		step();
		undoContract(candidate, actions);
		return;
	}
	cout << "NO MORE CANDIDATES?" << endl; //throw error
	return;
}

vector<int> MultiwayCutSolver::contract(int vertex) { 
	status[vertex] = 0;
	relaxationSolver.block(vertex);
	removeCandidate(vertex);
	vector<int> actions;

	for (int neighbor : graph -> getOutNeighbors(vertex)) {
		if (status[neighbor] != -1) {
			continue;
		}
		if (boundary[neighbor] == -1) { 
			boundary[neighbor] = boundary[vertex];
			addCandidate(neighbor); 
			actions.push_back(neighbor);
			continue;
		} 
		if (boundary[neighbor] != boundary[vertex]) {
			select(neighbor); 
			actions.push_back(neighbor);
		}
	}
	return actions;
}

void MultiwayCutSolver::undoContract(int vertex, vector<int>& actions) {
	status[vertex] = -1;
	relaxationSolver.pop();
	addCandidate(vertex);
	
	for (auto action : actions) {
		if (boundary[action] == boundary[vertex]) {
			boundary[action] = -1;
			removeCandidate(action);
			continue;
		}
		undoSelect(action);
	}
}
void MultiwayCutSolver::select(int vertex) {
	status[vertex] = 1;
	cur++;
	removeCandidate(vertex);
	relaxationSolver.select(vertex);
	currentSolution.push_back(vertex);
}


void MultiwayCutSolver::undoSelect(int vertex) {
	status[vertex] = -1;
	cur--;
	relaxationSolver.pop();
	candidates.insert(vertex);
	currentSolution.pop_back();
}

void MultiwayCutSolver::addCandidate(int vertex) {
	candidates.insert(vertex);
	relaxationSolver.addNeighbor(vertex);
}

void MultiwayCutSolver::removeCandidate(int vertex) {
	candidates.erase(vertex);
	relaxationSolver.removeNeighbor(vertex);
}

void MultiwayCutSolver::printCandidates() {
	vector<int> sortedCandidates;
	for (int candidate : candidates) {
		sortedCandidates.push_back(candidate);
	}
	sort(sortedCandidates.begin(), sortedCandidates.end());

	cout << "Active candidates: " << endl;
	for (int candidate : sortedCandidates) {
		cout << candidate << " ";	
	}
	cout << endl;
}

int MultiwayCutSolver::getLeaves() {
	return leaves;
}