#include "stdafx.h"
#include "graph.h"
#include "dgf_reader.h"

using namespace std;

static const string extension = ".dgf";

Graph DGFReader::read(string path, string filename) {
	ifstream infile(path + filename + extension);	
	string line, ignore;
	Graph* graph;
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