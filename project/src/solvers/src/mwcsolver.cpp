#include "stdafx.h"
#include <ilcplex/ilocplex.h>
#include "mwcsolver.h"
#include "lpsolver.h"


//victory condition: LP cost is 0

using namespace std;

MWCSolver::MWCSolver(int n, int t, vector<int> tlist, int** adj)
{
	//load input only
	nodes = n;
	terminals = t;
	termlist = tlist;
	adjacency = adj;
}


MWCSolver::~MWCSolver()
{

}

int MWCSolver::solve()
{
	lps.init(nodes, terminals, termlist, adjacency);

	//set up auxiliary data structures
	boundary = new int[nodes];
	status = new int[nodes];
	neighborhood = new unordered_set<int>[nodes];
	//opt_sol = new unordered_set<int>();
	//cur_sol = new unordered_set<int>;

	for (int i = 0; i < nodes; i++)
	{
		boundary[i] = -1;
		status[i] = -1;
		for (int j = 0; j < nodes; j++)
		{
			if (adjacency[i][j] == 1)
			{
				neighborhood[i].insert(j); //TODO?: dynamic status -1 neighborhood updates
			}
		}
	}

	for (auto t : termlist)
	{
		status[t] = 0;
		cout << "TERMINAL " << t << " with neighborhood";
		for (auto n : neighborhood[t])
		{
			cout << " " << n;
		}
		cout << endl;
	}

	cur = 0;
	opt = 0;

	//check feasibility and set up neighborhoods
	for (int i = 0; i < terminals; i++)
	{
		int t = termlist[i];
		for (int j = i + 1; j < terminals; j++)
		{
			int t2 = termlist[j];
			if (adjacency[t][t2] == 1)
			{
				//infeasible
				return -1;
			}
		}

		for (int j = 0; j < nodes; j++)
		{
			if (adjacency[t][j] == 1)
			{
				if (boundary[j] == -1)
				{
					boundary[j] = t;
					candidates.insert(j);
				}
				else //pick vertex for solution
				{
					if (status[j] == -1)
					{
						select(j);
					}
				}
			}
		}
	}

	//establish bound
	opt = static_cast<int> (2*lps.solve()); //assume k is not known

	//TODO: update opt_sol

	cout << "LP: " << opt/2 << endl;

	calc = true;

	step(true);

	//verify correctness

	LPSolver lps2;
	lps2.init(nodes, terminals, termlist, adjacency);

	for (auto v : opt_sol)
	{
		lps2.select(v);
	}
	//lps2.solve();

	cout << endl << "verified solution LP: " << lps2.solve() << endl;


	//finish

	return opt;
}

void MWCSolver::step(bool calc)
{
	cout << " STEP ";
	
	//if (calc) 
	{
		lp = lps.solve();
	}	

	//cout << "LP = " << lp << endl;
	//detect case

	if (lp == cur) //found solution
	{
		cout << "LEAF: solution found: ";
		if (opt > cur)
		{
			opt = cur;
			cout << "NEW OPT: " << opt;
			opt_sol.clear();
			//opt_sol.insert(cur_sol.begin, cur_sol.end);
			opt_sol.insert(opt_sol.begin(), cur_sol.begin(), cur_sol.end());
		}
		cout << endl;
		return;
	}
	else if (lp >= opt) //no hope to find better solution
	{
		cout << "LEAF: give up, LP = " << lp << " while OPT = " << opt << endl;
		return;
	}
	else 
	{
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

		
		for (auto c : candidates)
		{
			if (lps.isZero(c))
			{
				cout << "FOUND EASY CONTRACTION: " << c << endl;
				vector<int> actions = contract(c);

				step(false);
				undo_contract(c, actions);
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
			int c = *candidates.begin();
	//		cout << "BRANCH: " << c << endl;

			select(c);
			step(true);
			undo_select(c);

			vector<int> actions = contract(c);
			step(true);
			undo_contract(c, actions);
		}
		else {
			cout << "NO MORE CANDIDATES?" << endl;
		}
		return;
	}

	cout << "WTF" << endl;
}

vector<int> MWCSolver::contract(int v)
{
	//cout << "CONTRACT: " << v << endl;
	status[v] = 0;
	lps.block(v);
	remCandidate(v);
	//cout << "remove " << v << " from candidates" << endl;
	vector<int> actions;

	for (auto u : neighborhood[v])
	{
		if (status[u] == -1)
		{
			if (boundary[u] == -1) //update boundary
			{
				boundary[u] = boundary[v];
				addCandidate(u); //u was no candidate before
				//cout << "add " << u << " to candidates" << endl;
				actions.push_back(u);
			} 
			else if (boundary[u] != boundary[v]) //neighbor must be picked
			{
				select(u); 
				actions.push_back(u);
			}
		}
	}
	
	return actions;
}

void MWCSolver::undo_contract(int v, vector<int> actions)
{
	status[v] = -1;
	lps.pop();
	addCandidate(v);
	
	for (auto u : actions)
	{
		if (boundary[u] == boundary[v])
		{
			boundary[u] = -1;
			remCandidate(u);
		}
		else
		{
			undo_select(u);
		}
	}
}
void MWCSolver::select(int v)
{
	//cout << "SELECT: " << v << endl;
	status[v] = 1;
	cur++;
	remCandidate(v);
	lps.select(v);
	//cout << "remove " << v << " from candidates" << endl;
	cur_sol.push_back(v);
}


void MWCSolver::undo_select(int v)
{
	//cout << "UNDO_SELECT: " << v << endl;

	status[v] = -1;
	cur--;
	lps.pop();
	candidates.insert(v);
	//cout << "add " << v << " to candidates" << endl;
	cur_sol.pop_back();
}

void MWCSolver::addCandidate(int v)
{
	candidates.insert(v);
	lps.addNeighbor(v);
}

void MWCSolver::remCandidate(int v)
{
	candidates.erase(v);
	lps.remNeighbor(v);
}