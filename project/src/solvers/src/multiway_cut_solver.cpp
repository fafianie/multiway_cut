#include "stdafx.h"
#include <ilcplex/ilocplex.h>
#include "multiway_cut_solver.h"
#include "multiway_cut_relaxation_solver.h"
#include "graph.h"


//victory condition: LP cost is 0

using namespace std;

MultiwayCutSolver::MultiwayCutSolver() {
	//load input only
	//TODO: push this to solve function
}


MultiwayCutSolver::~MultiwayCutSolver(){ 
}

int MultiwayCutSolver::solve(Graph& inputGraph) {
	//TODO: assume graph is normalized
	cout << endl << "start solve" << endl;
	graph = &inputGraph;
	unordered_set<int> vertices = graph -> getVertices();
	vector<int> terminals;
	//TODO: do we really need a vector?
	for (int terminal : graph -> getTerminals()) {
		terminals.push_back(terminal);
	}
	
	relaxationSolver.init(*graph);

	//set up auxiliary data structures TODO: USE VECTORS!!! (put in graph?)
	boundary.assign(vertices.size(), -1);
	status.assign(vertices.size(), -1);
	//opt_sol = new unordered_set<int>();
	//cur_sol = new unordered_set<int>;

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

	//TODO: update opt_sol

	cout << "LP: " << opt/2 << endl;

	stepsTaken = 0;
	step();

	//verify correctness

	MultiwayCutRelaxationSolver lps2;
	lps2.init(*graph);

	for (auto v : opt_sol) {
		lps2.select(v);
	}
	//lps2.solve();

	cout << endl << "final solution: " << opt << endl;
	cout << endl << "verified solution LP: " << lps2.solve() << endl; //TODO: ERROR IF NOT THE SAME


	//finish

	return opt;
}

void MultiwayCutSolver::step() {
	//if (stepsTaken > 100000) {
	//	cout << "too many steps" << endl;
	//	throw runtime_error("Too many steps");
	//}
	stepsTaken++;
	//cout << " STEP " << endl;
	//printCandidates();
	
	//if (calc) { //TODO~!?
		lp = relaxationSolver.solve();
	//}	

	//cout << "LP = " << lp << endl;
	//detect case

	if (lp == cur) {//found solution
		//cout << "LEAF: solution found: ";
		if (opt > cur) {
			opt = cur;
			//cout << "NEW OPT: " << opt;
			optimalSolution.clear();
			//opt_sol.insert(cur_sol.begin, cur_sol.end);
			optimalSolution.insert(optimalSolution.begin(), currentSolution.begin(), currentSolution.end());
		}
		cout << endl;
		return;
	}
	if (lp >= opt) { //no hope to find better solution
		//cout << "LEAF: give up, LP = " << lp << " while OPT = " << opt << endl;
		return;
	}
	//	cout << "LOOKING TO CONTRACT" << endl;
	//	cout << "#CANDIDATES: " << candidates.size() << endl;

		//look for easy candidate (already 0 in lp)

	bool easy = false;
	
	vector<int> easyContractions;

	for (auto candidate : candidates) {
		if (lps.isZero(candidate)) {
	//			cout << " begin loop" << endl;
		easy = true;
	//			cout << "FOUND EASY CONTRACTION: " << c << endl;
				//vector<int> actions = contract(c);				
				//all_actions.push_back(actions);
		easyContractions.push_back(candidate);	
	//			cout << " end loop" << endl;
		}
	}

	
	if (easy) {
		vector<vector<int>> allActions;
		for (auto candidate : easyContractions) {		
			vector<int> actions = contract(candidate);
			allActions.push_back(actions);
		}

	//		cout << "before step" << endl;
		step(false);

		for (int i = easyContractions.size() - 1; i > -1; i--) {
			undo_contract(easyContractions[i], allActions[i]);
		}
			
		return;
	}

		
	/*for (auto candidate : candidates) {
		if (lps.isZero(candidate)) {
			//cout << "FOUND EASY CONTRACTION: " << candidate << endl;
			vector<int> actions = contract(candidate);

			step(false);
			undo_contract(candidate, actions);
			return;
		}
	}*/
		
		//

		//TODO: experiment: look for easy candidates only*/
		
		
	vector<int> candidatesCopy;
	for (auto candidate : candidates) {
		candidatesCopy.push_back(candidate);
	}

	for (auto const& candidate : candidatesCopy) { //try to find candidate to contract on (could probably save some work here by remembering some values?)		
		vector<int> actions = contract(candidate);
		double lp0 = lps.solve();
		if (lp0 == lp) {
				//cout << "FOUND NORMAL CONTRACTION: " << c << endl;

			step(true);
			undo_contract(candidate, actions);
			return;
		}
		undo_contract(candidate, actions);

			//bool incorrect = false;
			//if (c2.size() != candidates.size())
			//{
			//	incorrect = true;
			//}
			/*else
			{
				for (auto cc : c2)
				{
					if (std::find(candidates.begin(), candidates.end(), cc) != candidates.end()) {

					}
					else {
						incorrect = true;
					}
				}
			}*/
	} //

		//branch on arbitrary candidate
	if (candidates.size() > 0) {
		int candidate = *candidates.begin();
	//		cout << "BRANCH: " << c << endl;

		select(candidate);
		step();
		undo_select(candidate);

		vector<int> actions = contract(candidate);
		step();
		undo_contract(candidate, actions);
	}
	else {
		cout << "NO MORE CANDIDATES?" << endl;
	}
	return;
}

vector<int> MultiwayCutSolver::contract(int vertex) { 
	//cout << endl << "CONTRACT: " << vertex << endl;
	status[vertex] = 0;
	lps.block(vertex);
	removeCandidate(vertex);
	//cout << "remove " << vertex << " from candidates" << endl;
	vector<int> actions;

	for (int neighbor : graph -> getOutNeighbors(vertex)) {
		if (status[neighbor] != -1) {
			continue;
		}
		if (boundary[neighbor] == -1) { //update boundary
			boundary[neighbor] = boundary[vertex];
			addCandidate(neighbor); //u was no candidate before
			//cout << "add " << neighbor << " to candidates" << endl;
			actions.push_back(neighbor);
			continue;
		} 
		if (boundary[neighbor] != boundary[vertex]) { //neighbor must be picked
			//cout << "must pick neighbor" << endl;
			select(neighbor); 
			actions.push_back(neighbor);
		}
	}
	//cout << endl << "done contracting" << endl;
	return actions;
}

void MultiwayCutSolver::undo_contract(int vertex, vector<int> actions) {
	//cout << endl << "UNDO CONTRACT: " << vertex << endl;
	status[vertex] = -1;
	lps.pop();
	addCandidate(vertex);
	
	for (auto action : actions) {
		if (boundary[action] == boundary[vertex]) {
			boundary[action] = -1;
			removeCandidate(action);
			continue;
		}
		undo_select(action);
	}
	//cout << "done undo contract" << endl;
}
void MultiwayCutSolver::select(int vertex) {
	//cout << "SELECT: " << vertex << endl;
	status[vertex] = 1;
	cur++;
	removeCandidate(vertex);
	lps.select(vertex);
	//cout << "remove " << v << " from candidates" << endl;
	cur_sol.push_back(vertex);
	//cout << "DONE SELECT" << endl;
}


void MultiwayCutSolver::undo_select(int vertex) {
	//cout << endl << "UNDO_SELECT: " << vertex << endl;

	status[vertex] = -1;
	cur--;
	lps.pop();
	candidates.insert(vertex);
	//cout << "add " << v << " to candidates" << endl;
	cur_sol.pop_back();
	//cout << "DONE UNDO SELECT" << endl;
}

void MultiwayCutSolver::addCandidate(int vertex) {
	candidates.insert(vertex);
	lps.addNeighbor(vertex);
}

void MultiwayCutSolver::removeCandidate(int vertex) {
	candidates.erase(vertex);
	lps.removeNeighbor(vertex);
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




