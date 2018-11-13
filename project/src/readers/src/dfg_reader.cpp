#include "stdafx.h"
#include "graph.h"
#include "dfg_reader.h"

using namespace std;

Graph DFGReader::read(string path, string filename) {
	ifstream infile(path + filename);	
	string line, ignore;
	Graph *graph;
	while (getline(infile, line)) { 
		istringstream iss(line);
		if (line[0] == 'p') {
			int vertices, edges;
			if (!(iss >> ignore >> ignore >> vertices >> edges)) { 
				break; 
			}
			graph = new Graph(vertices);
		} else if (line[0] == 'e') {
			int i, j;
			if (!(iss >> ignore >> i >> j)) { 
				break; 
			}
			graph -> addEdge(i, j);
		} else if (line[0] == 't') {
			int t;
			if (!(iss >> ignore >> t)) {
				break;
			}
			graph -> addTerminal(t);
		}
	}	
	return *graph;
}