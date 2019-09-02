#include "stdafx.h"
#include <ilcplex/ilocplex.h>
#include "mwcsolver.h"
#include "lpsolver.h"
#include "graph.h"


//victory condition: LP cost is 0

using namespace std;

MWCSolver::MWCSolver() {
	//load input only
	//TODO: push this to solve function
}


MWCSolver::~MWCSolver(){ 
}

int MWCSolver::solve(Graph& inputGraph) {
	cout << endl << "start solve" << endl;
	graph = &inputGraph;
	int vertices = graph -> getVertices();
	vector<int> terminals;
	for (int terminal : graph -> getTerminals()) {
		terminals.push_back(terminal);
	}
	
	lps.init(*graph);

	//set up auxiliary data structures TODO: USE VECTORS!!! (put in graph?)
	boundary.assign(vertices, -1);
	status.assign(vertices, -1);
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
	for (int i = 0; i < terminals.size(); i++)	{
		int terminal = terminals[i];
		for (int j = i + 1; j < terminals.size(); j++)	{
			int otherTerminal = terminals[j];
			if (graph -> isOutNeighbor(terminal, otherTerminal)) {
				//infeasible
				return -1;
			}
		}

		for (int vertex = 0; vertex < vertices; vertex++)	{
			if (graph -> isOutNeighbor(terminal, vertex)) {
				if (boundary[vertex] == -1) {
					boundary[vertex] = terminal;
					candidates.insert(vertex);
					break;
				}
				if (status[vertex] == -1) {
					select(vertex);
				}
			}
		}
	}

	//establish bound
	opt = static_cast<int> (2 * lps.solve()); //assume k is not known

	//TODO: update opt_sol

	cout << "LP: " << opt/2 << endl;

	
	step(true);

	//verify correctness

	LPSolver lps2;
	lps2.init(*graph);

	for (auto v : opt_sol) {
		lps2.select(v);
	}
	//lps2.solve();

	cout << endl << "verified solution LP: " << lps2.solve() << endl; //TODO: ERROR IF NOT THE SAME


	//finish

	return opt;
}

void MWCSolver::step(bool calc) {
	cout << " STEP ";
	
	//if (calc) { TODO~!?
		lp = lps.solve();
	//}	

	//cout << "LP = " << lp << endl;
	//detect case

	if (lp == cur) {//found solution
		cout << "LEAF: solution found: ";
		if (opt > cur) {
			opt = cur;
			cout << "NEW OPT: " << opt;
			opt_sol.clear();
			//opt_sol.insert(cur_sol.begin, cur_sol.end);
			opt_sol.insert(opt_sol.begin(), cur_sol.begin(), cur_sol.end());
		}
		cout << endl;
		return;
	}
	else if (lp >= opt) { //no hope to find better solution
		cout << "LEAF: give up, LP = " << lp << " while OPT = " << opt << endl;
		return;
	}
	else {
	//	cout << "LOOKING TO CONTRACT" << endl;
	//	cout << "#CANDIDATES: " << candidates.size() << endl;

		//look for easy candidate (already 0 in lp)

		bool easy = false;
		vector<vector<int>> all_actions;
		vector<int> easy_contractions;

		/*for (auto c : candidates)
		{
			if (lps.isZero(c))
			{
	//			cout << " begin loop" << endl;
				easy = true;
	//			cout << "FOUND EASY CONTRACTION: " << c << endl;
				//vector<int> actions = contract(c);				
				//all_actions.push_back(actions);
				easy_contractions.push_back(c);	
	//			cout << " end loop" << endl;
			}
		}

		if (easy) {
			for (auto c : easy_contractions)
			{
				vector<int> actions = contract(c);
				all_actions.push_back(actions);
			}

	//		cout << "before step" << endl;
			step(false);

			for (int i = easy_contractions.size()-1; i > -1; i--) 
			{
				undo_contract(easy_contractions[i], all_actions[i]);
			}
			
			return;
		}*/

		
		for (auto candidate : candidates) {
			if (lps.isZero(candidate)) {
				cout << "FOUND EASY CONTRACTION: " << candidate << endl;
				vector<int> actions = contract(candidate);

				step(false);
				undo_contract(candidate, actions);
				return;
			}
		}
		
		//

		//TODO: experiment: look for easy candidates only*/
		
		
		/*vector<int> c2;
		for (auto c : candidates) {
			c2.push_back(c);
		}

		for (auto c : c2) //try to find candidate to contract on (could probably save some work here by remembering some values?)
		{			
			vector<int> actions = contract(c);
			double lp0 = lps.solve();
			if (lp0 == lp)
			{
				cout << "FOUND NORMAL CONTRACTION: " << c << endl;

				step();
				undo_contract(c, actions);
				return;
			}
			undo_contract(c, actions);

			bool incorrect = false;
			if (c2.size() != candidates.size())
			{
				incorrect = true;
			}
			else
			{
				for (auto cc : c2)
				{
					if (std::find(candidates.begin(), candidates.end(), cc) != candidates.end()) {

					}
					else {
						incorrect = true;
					}
				}
			}
		} //*/

		//branch on arbitrary candidate
		if (candidates.size() > 0) {
			int candidate = *candidates.begin();
	//		cout << "BRANCH: " << c << endl;

			select(candidate);
			step(true);
			undo_select(candidate);

			vector<int> actions = contract(candidate);
			step(true);
			undo_contract(candidate, actions);
		}
		else {
			cout << "NO MORE CANDIDATES?" << endl;
		}
		return;
	}

	cout << "WTF" << endl;
}

vector<int> MWCSolver::contract(int vertex) { 
	cout << endl << "CONTRACT: " << vertex << endl;
	status[vertex] = 0;
	lps.block(vertex);
	removeCandidate(vertex);
	cout << "remove " << vertex << " from candidates" << endl;
	vector<int> actions;

	for (int neighbor : graph -> getOutNeighbors(vertex)) {
		if (status[neighbor] != -1) {
			break;
		}
		if (boundary[neighbor] == -1) { //update boundary
			boundary[neighbor] = boundary[vertex];
			addCandidate(neighbor); //u was no candidate before
			cout << "add " << neighbor << " to candidates" << endl;
			actions.push_back(neighbor);
			break;
		} 
		if (boundary[neighbor] != boundary[vertex]) { //neighbor must be picked
			cout << "must pick neighbor" << endl;
			select(neighbor); 
			actions.push_back(neighbor);
		}
	}
	cout << endl << "done contracting" << endl;
	return actions;
}

void MWCSolver::undo_contract(int vertex, vector<int> actions) {
	cout << endl << "UNDO CONTRACT: " << vertex << endl;
	status[vertex] = -1;
	lps.pop();
	addCandidate(vertex);
	
	for (auto action : actions) {
		if (boundary[action] == boundary[vertex]) {
			boundary[action] = -1;
			removeCandidate(action);
			break;
		}
		undo_select(action);
	}
	cout << "done undo contract" << endl;
}
void MWCSolver::select(int vertex) {
	cout << "SELECT: " << vertex << endl;
	status[vertex] = 1;
	cur++;
	removeCandidate(vertex);
	lps.select(vertex);
	//cout << "remove " << v << " from candidates" << endl;
	cur_sol.push_back(vertex);
	cout << "DONE SELECT" << endl;
}


void MWCSolver::undo_select(int vertex) {
	cout << endl << "UNDO_SELECT: " << vertex << endl;

	status[vertex] = -1;
	cur--;
	lps.pop();
	candidates.insert(vertex);
	//cout << "add " << v << " to candidates" << endl;
	cur_sol.pop_back();
	cout << "DONE UNDO SELECT" << endl;
}

void MWCSolver::addCandidate(int vertex) {
	candidates.insert(vertex);
	lps.addNeighbor(vertex);
}

void MWCSolver::removeCandidate(int vertex) {
	candidates.erase(vertex);
	lps.removeNeighbor(vertex);
}