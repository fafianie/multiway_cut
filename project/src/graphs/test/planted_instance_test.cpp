#include "stdafx.h"
#include "graph.h"

using namespace std;

int main(int argc, char* argv[]) {
	Graph graph = Graph(7);
	graph.addTerminal(2);
	graph.addTerminal(5);
	graph.addEdge(0, 1);
	graph.addEdge(1, 2);
	graph.addEdge(1, 3);
	graph.addEdge(2, 3);
	graph.addEdge(2, 5);
	graph.addEdge(3, 4);
	graph.addEdge(3, 5);
	graph.addEdge(4, 5);
	graph.addArc(4, 6);
	graph.addArc(5, 6);
	cout << "Graph created" << endl;
	graph.display();
	graph.remove(1);
	cout << "Removed 1" << endl;
	graph.display();
	graph.contract(5);
	cout << "Contracted 5" << endl;
	graph.display();
	graph.normalize();
	cout << "Normalized" << endl;
	graph.display();

	Graph expectedGraph = Graph(5);
	expectedGraph.addTerminal(1);
	expectedGraph.addEdge(1, 2);
	expectedGraph.addEdge(1, 3);
	expectedGraph.addArc(1, 4);
	expectedGraph.addEdge(2, 3);
	expectedGraph.addArc(2, 4);
	expectedGraph.addArc(3, 4);
	cout << "Expected graph created" << endl;
	expectedGraph.display();
	
	if (!graph.equals(expectedGraph)) {
		cout << "Error: input graph is not equal to output graph after operations are applied." << endl;
		return 1;
	}

	return 0;
}