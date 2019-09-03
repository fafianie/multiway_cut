#include "stdafx.h"
#include "graph.h"
#include "dgf_writer.h"

using namespace std;

static const string extension = ".dgf";

void DGFWriter::write(Graph& graph, string path, string filename, string comment) {
	ofstream outfile(path + filename + extension);
	outfile << "c " << comment;
	vector<int> vertices;
	int edges = 0;
	for (int vertex : graph.getVertices()) {
		vertices.push_back(vertex);
		for (int outNeighbor : graph.getOutNeighbors(vertex)) {
			edges++;
		}
	}
	sort(vertices.begin(), vertices.end());
	
	outfile << endl << "p edge " << vertices.size() << " " << edges;
	for (int indexU = 0; indexU < vertices.size(); indexU ++) {
		for (int indexV = indexU + 1; indexV < vertices.size(); indexV++) {
			int u = vertices[indexU];
			int v = vertices[indexV];
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