#include "stdafx.h"
#include "graph.h"
#include "dgf_reader.h"

using namespace std;

static const string extension = ".dgf";

Graph DGFReader::read(string path, string filename) {
	ifstream infile(path + filename + extension);	
	cout << "opened stream for " << filename << extension << endl;
	string line, ignore;
	Graph* graph;
	int linecount = 1;
	cout << "before first line" << endl;
	while (getline(infile, line)) { 
		cout << "error at line " << linecount << endl;
		linecount++;
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