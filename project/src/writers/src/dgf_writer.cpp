#include "stdafx.h"
#include "graph.h"
#include "dgf_writer.h"

using namespace std;

static const string extension = ".dgf";

void DGFWriter::write(Graph& graph, string path, string filename, string comment) {
	ofstream outfile(path + filename + extension);
	outfile << "c " << comment;
	int vertices = graph.getVertices();
	outfile << endl << "p edge " << vertices << " " << graph.getEdges();
	for (int u = 0; u < vertices; u ++) {
		for (int v = u + 1; v < vertices; v++) {
			if (graph.isInNeighbor(u, v)) {
				outfile << endl << "e " << u << " " << v;
			}
		}
	}
	vector<int> terminals;
	for (int terminal : graph.getTerminals()) {
		terminals.push_back(terminal);
	}
	sort(terminals.begin(), terminals.end());
	for (int terminal : terminals) {
		outfile << endl << "t " << terminal;
	}
	outfile.close();
}