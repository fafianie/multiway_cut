#include "stdafx.h"
#include <ilcplex/ilocplex.h>
#include "lpsolver.h"

ILOSTLBEGIN
//using namespace std;
// input: adjacency matrix, number of terminals, number of vertices,

LPSolver::LPSolver()
{
}

LPSolver::LPSolver(int nodes, int terminals, vector<int> termlist, int** adj)
{
	init(nodes, terminals, termlist, adj);
}

void LPSolver::init(int nodes, int terminals, vector<int> termlist, int** adj)
{
	try 
	{
		IloModel m(env);
		model = m;

		IloNumVarArray d(env, nodes, 0.0, IloInfinity); //TODO check difference in runtime using 1.0 as upper bound
		/*for (int i = 0; i < terminals; i++)
		{
			d[termlist[i] - 1] = IloNumVar(env, 0.0, 0.0);
		}*/
		dist = d;

		IloNumVarArray y(env, nodes*terminals, 0.0, IloInfinity);


		// initialize for warm start
		IloNumVarArray wd(env);
		IloNumArray wv(env);
		for (int i = 0; i < nodes; i++)
		{
			wd.add(d[i]);
			wv.add(0.0);
		}
		warmvars = wd;
		warmvals = wv;


		// y_i,k = y[i*k-1]

		model.add(d);
		model.add(y);

		model.add(IloMinimize(env, IloSum(d)));

		IloRangeArray c(env);

		//neighbor distance constraints
		for (int u = 0; u < nodes; u++)
		{
			for (int v = 0; v < nodes; v++)
			{
				if (adj[u][v] == 1) 
				{
					for (int j = 0; j < terminals; j++)
					{
						int offset = j*nodes;
						c.add(y[offset + v] - y[offset + u] - d[v] <= 0);
						c.add(y[offset + u] - y[offset + v] - d[u] <= 0);
					}
				}
			}
		}

		//terminal distance constraints
		for (int j = 0; j < terminals; j++)
		{
			int offset = j*nodes;
			c.add(y[offset+(termlist[j])] == 0);
		}

		//terminal seperation constraints
		for (int i = 0; i < terminals; i++)
		{
			int offset = i*nodes;
			for (int j = 0; j < terminals; j++) 
			{
				if (i != j)
				{
					c.add(y[offset+(termlist[j])] >= 1);
				}
			}
		}

		//ban terminals from solution
		for (int i = 0; i < terminals; i++)
		{
			c.add(d[(termlist[i])] == 0);
		}

		model.add(c);


		IloCplex cp(model);
		cplex = cp;
		cplex.setOut(env.getNullStream());
		cplex.setWarning(env.getNullStream());
	}
	catch (IloException& e) {
		cerr << "Concert exception caught: " << e << endl;
	}
	catch (...) {
		cerr << "Unknown exception caught: " << endl;
	}

}

void LPSolver::block(int v)
{
	IloRangeArray c(env);
	c.add(dist[v] == 0);
	model.add(c);
	q.push(c);

	//cout << "ADDED CONSTRAINT " << c << endl;
	//cout << "FRONT OF Q " << q.back();

}

void LPSolver::select(int v)
{
	IloRangeArray c(env);
	c.add(dist[v] == 1);
	model.add(c);
	q.push(c);
	warmvals[v] = 1.0;
}

void LPSolver::pop()
{
	//cout << "IS CONSTRAINT?: " << q.front() << endl;
	model.remove(q.top());
	q.pop();
}

void LPSolver::constraints() 
{
	//model.getProperties.
}


double LPSolver::solve() 
{
	try
	{
		cplex.setStart(warmvals, NULL, warmvars, NULL, NULL, NULL);
		cplex.solve();
		//cplex.
		
		//cplex.addMIPStart(warmvars, warmvals);
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

bool LPSolver::isZero(int v)
{
	IloNumArray vals(env);
	cplex.getValues(vals, dist);
	return (vals[v] == 0);
}


LPSolver::~LPSolver()
{
	env.end();
}

/*void LPSolver::unSelect(int v)
{
	warmvals[v] = 0.0;
}*/

void LPSolver::addNeighbor(int v)
{
	warmvals[v] = 0.5;
}

void LPSolver::remNeighbor(int v)
{
	warmvals[v] = 0.0;
}




// functions: initialize problem, add constraint, remove constraint (always the last one added), remove last x constraints
//
