#include "stdafx.h"
#include "graph.h"
#include "multiway_cut_solver.h"
#include "dgf_writer.h"
#include "metrics_writer.h"

using namespace std;

const int repetitions = 10;
const string path = "../../resources/instance_generation";

int main(int argc, char* argv[]) {
		
	vector<vector<int>> instances;
	
	//3 terminals
							//  vertices	clusters	terminals	edges		hubSize		hubEdges	budget	
	vector<int> instance331{	100			,4			,3			,500		,5			,5			,3	}; 
	vector<int> instance332{	250			,4			,3			,1750		,5			,5			,3	};  
	vector<int> instance333{	500			,4			,3			,4000		,5			,5			,3	}; 
	vector<int> instance334{	750			,4			,3			,5750		,5			,5			,3	}; 
	vector<int> instance335{	1000		,4			,3			,8000		,5			,5			,3	}; 
	vector<int> instance336{	1250		,4			,3			,10500		,5			,5			,3	};  
	vector<int> instance337{	1500		,4			,3			,12000		,5			,5			,3	};
	
	instances.push_back(instance331);
	instances.push_back(instance332);
	instances.push_back(instance333);
	instances.push_back(instance334);
	instances.push_back(instance335);
	instances.push_back(instance336);
	instances.push_back(instance337);
	
							//  vertices	clusters	terminals	edges		hubSize		hubEdges	budget	
	vector<int> instance341{	100			,4			,3			,500		,6			,6			,4	}; 
	vector<int> instance342{	250			,4			,3			,1750		,6			,6			,4	};  
	vector<int> instance343{	500			,4			,3			,4000		,6			,6			,4	}; 
	vector<int> instance344{	750			,4			,3			,5750		,6			,6			,4	}; 
	vector<int> instance345{	1000		,4			,3			,8000		,6			,6			,4	}; 
	vector<int> instance346{	1250		,4			,3			,10500		,6			,6			,4	};  
	vector<int> instance347{	1500		,4			,3			,12000		,6			,6			,4	};
	
	instances.push_back(instance341);
	instances.push_back(instance342);
	instances.push_back(instance343);
	instances.push_back(instance344);
	instances.push_back(instance345);
	instances.push_back(instance346);
	instances.push_back(instance347);
	
							//  vertices	clusters	terminals	edges		hubSize		hubEdges	budget	
	vector<int> instance351{	100			,4			,3			,500		,7			,7			,5	}; 
	vector<int> instance352{	250			,4			,3			,1750		,7			,7			,5	};  
	vector<int> instance353{	500			,4			,3			,4000		,7			,7			,5	}; 
	vector<int> instance354{	750			,4			,3			,5750		,7			,7			,5  }; 
	vector<int> instance355{	1000		,4			,3			,8000		,7			,7			,5	}; 
	vector<int> instance356{	1250		,4			,3			,10500		,7			,7			,5	};  
	vector<int> instance357{	1500		,4			,3			,12000		,7			,7			,5	};
	
	instances.push_back(instance351);
	instances.push_back(instance352);
	instances.push_back(instance353);
	instances.push_back(instance354);
	instances.push_back(instance355);
	instances.push_back(instance356);
	instances.push_back(instance357);
	
							// 	vertices	clusters	terminals	edges		hubSize		hubEdges	budget	
	vector<int> instance361{	100			,4			,3			,500		,8			,8			,6	}; 
	vector<int> instance362{	250			,4			,3			,1750		,8			,8			,6	};  
	vector<int> instance363{	500			,4			,3			,4000		,8			,8			,6	}; 
	vector<int> instance364{	750			,4			,3			,5750		,8			,8			,6	}; 
	vector<int> instance365{	1000		,4			,3			,8000		,8			,8			,6	}; 
	vector<int> instance366{	1250		,4			,3			,10500		,8			,8			,6	};  
	vector<int> instance367{	1500		,4			,3			,12000		,8			,8			,6	};
	
	instances.push_back(instance361);
	instances.push_back(instance362);
	instances.push_back(instance363);
	instances.push_back(instance364);
	instances.push_back(instance365);
	instances.push_back(instance366);
	instances.push_back(instance367);
	
							//  vertices	clusters	terminals	edges		hubSize		hubEdges	budget	
	vector<int> instance371{	100			,4			,3			,500		,9			,9			,7	}; 
	vector<int> instance372{	250			,4			,3			,1750		,9			,9			,7	};  
	vector<int> instance373{	500			,4			,3			,4000		,9			,9			,7	}; 
	vector<int> instance374{	750			,4			,3			,5750		,9			,9			,7	}; 
	vector<int> instance375{	1000		,4			,3			,8000		,9			,9			,7	}; 
	vector<int> instance376{	1250		,4			,3			,10500		,9			,9			,7	};  
	vector<int> instance377{	1500		,4			,3			,12000		,9			,9			,7	};
	
	instances.push_back(instance371);
	instances.push_back(instance372);
	instances.push_back(instance373);
	instances.push_back(instance374);
	instances.push_back(instance375);
	instances.push_back(instance376);
	instances.push_back(instance377);
	
	//4 terminals
							//  vertices	clusters	terminals	edges		hubSize		hubEdges	budget	
	vector<int> instance431{	100			,5			,4			,500		,5			,5			,3	}; 
	vector<int> instance432{	250			,5			,4			,1750		,5			,5			,3	};  
	vector<int> instance433{	500			,5			,4			,4000		,5			,5			,3	}; 
	vector<int> instance434{	750			,5			,4			,5750		,5			,5			,3	}; 
	vector<int> instance435{	1000		,5			,4			,8000		,5			,5			,3	}; 
	vector<int> instance436{	1250		,5			,4			,10500		,5			,5			,3	};  
	vector<int> instance437{	1500		,5			,4			,12000		,5			,5			,3	};
	
	instances.push_back(instance431);
	instances.push_back(instance432);
	instances.push_back(instance433);
	instances.push_back(instance434);
	instances.push_back(instance435);
	instances.push_back(instance436);
	instances.push_back(instance437);
	
							//  vertices	clusters	terminals	edges		hubSize		hubEdges	budget	
	vector<int> instance441{	100			,5			,4			,500		,6			,6			,4	}; 
	vector<int> instance442{	250			,5			,4			,1750		,6			,6			,4	};  
	vector<int> instance443{	500			,5			,4			,4000		,6			,6			,4	}; 
	vector<int> instance444{	750			,5			,4			,5750		,6			,6			,4	}; 
	vector<int> instance445{	1000		,5			,4			,8000		,6			,6			,4	}; 
	vector<int> instance446{	1250		,5			,4			,10500		,6			,6			,4	};  
	vector<int> instance447{	1500		,5			,4			,12000		,6			,6			,4	};
	
	instances.push_back(instance441);
	instances.push_back(instance442);
	instances.push_back(instance443);
	instances.push_back(instance444);
	instances.push_back(instance445);
	instances.push_back(instance446);
	instances.push_back(instance447);
	
							//  vertices	clusters	terminals	edges		hubSize		hubEdges	budget	
	vector<int> instance451{	100			,5			,4			,500		,7			,7			,5	}; 
	vector<int> instance452{	250			,5			,4			,1750		,7			,7			,5	};  
	vector<int> instance453{	500			,5			,4			,4000		,7			,7			,5	}; 
	vector<int> instance454{	750			,5			,4			,5750		,7			,7			,5	}; 
	vector<int> instance455{	1000		,5			,4			,8000		,7			,7			,5	}; 
	vector<int> instance456{	1250		,5			,4			,10500		,7			,7			,5	};  
	vector<int> instance457{	1500		,5			,4			,12000		,7			,7			,5	};
	
	instances.push_back(instance451);
	instances.push_back(instance452);
	instances.push_back(instance453);
	instances.push_back(instance454);
	instances.push_back(instance455);
	instances.push_back(instance456);
	instances.push_back(instance457);
	
	//break the algorithm
							//  vertices	clusters	terminals	edges		hubSize		hubEdges	budget	
	vector<int> instance001{	1750		,6			,5			,13500		,9			,9			,8	}; 
	vector<int> instance002{	2000		,7			,6			,15000		,10			,10			,9	};  
	vector<int> instance003{	2500		,8			,7			,16500		,11			,11			,10	}; 
	vector<int> instance004{	2750		,9			,8			,18000		,12			,12			,11	}; 
	vector<int> instance005{	3000		,10			,9			,19500		,13			,13			,12	}; 
	vector<int> instance006{	3250		,11			,10			,21000		,14			,14			,13	};  
	vector<int> instance007{	3500		,12			,11			,22500		,15			,15			,14	};
	
	instances.push_back(instance001);
	instances.push_back(instance002);
	instances.push_back(instance003);
	instances.push_back(instance004);
	instances.push_back(instance005);
	instances.push_back(instance006);
	instances.push_back(instance007);
	

	for (vector<int> instance : instances) {
		int vertices = instance[0];
		int clusters = instance[1];
		int terminals = instance[2];
		int edges = instance[3];
		int hubSize = instance[4];
		int hubEdges = instance[5];
		int budget = instance[6];
		string name = "" + vertices + "_" + edges + "_" + terminals "_" + budget;
		string comment = "Vertices: " + vertices + ", Edges:" + edges + ", Clusters:" + clusters + ", Terminals: " + terminals + ", HubSize: " + hubSize + ", HubEdges: " + hubEdges + ", Budget:" + budget;
		Metrics metrics;
		
		for (int repetition = 0; repetition < repetitions; repetition++) {
			PlantedInstance graph(vertices, clusters, terminals, edges, hubSize, hubEdges, budget);
			string dgfName = name + "_(" + repetition + ")" ;
			cout << "generating " << dgfName << endl;
			MultiwayCutSolver solver;
			
			auto start = chrono::high_resolution_clock::now();
			int solutionCost = solver.solve(graph);
			auto finish = chrono::high_resolution_clock::now();
			int duration = chrono::duration_cast<chrono::milliseconds>(finish - start).count();
			int leaves = solver.getLeaves();
			
			map<string, string> entry;
			entry.insert(make_pair("graph", dgfName));
			entry.insert(make_pair("vertices", "" + vertices));
			entry.insert(make_pair("clusters", "" + clusters));
			entry.insert(make_pair("terminals", "" + terminals));
			entry.insert(make_pair("edges", "" + edges));
			entry.insert(make_pair("hubSize", "" + hubSize));
			entry.insert(make_pair("hubEdges", "" + hubEdges));
			entry.insert(make_pair("budget", "" + budget));
			entry.insert(make_pair("solutionCost", "" + solutionCost));
			entry.insert(make_pair("duration", "" + duration));
			entry.insert(make_pair("leaves", "" + leaves));
			metrics.addEntry(entry);
			
			string dgfName = name + "_(" + repetition + ")" ;
			string dgfComment = comment + " || Repetition: " + repetition + ", SolutionCost: " + solutionCost + ", Duration: " + duration + ", Leaves:" + leaves;
			DGFWriter::write(input, path, dgfName, dgfComment);
			
			
		}
		string metricsName = name + "_metrics";
		string metricsComment = "Metrics for " + comment;
		MetricsWriter::write(metrics, path, metricsName, "");
	}
	return 0;
}