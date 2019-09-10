#include "stdafx.h"
#include "graph.h"
#include "decorated_graph.h"

using namespace std;

int main(int argc, char* argv[]) {
	
	Graph graph(10);
	graph.addEdge(0, 1);
	graph.addEdge(1, 2);
	graph.addEdge(1, 3);
	graph.addEdge(1, 5);
	graph.addEdge(2, 3);
	graph.addEdge(3, 4);
	graph.addEdge(4, 5);
	graph.addEdge(4, 6);
	graph.addEdge(4, 7);
	graph.addEdge(5, 6);
	graph.addEdge(6, 7);
	graph.addEdge(6, 9);
	graph.addEdge(7, 8);
	graph.addEdge(8, 9);
	graph.addTerminal(2);
	graph.addTerminal(7);
	
	DecoratedGraph decoratedGraph(graph, 2);
	
	Graph expectedGraph(20);
	expectedGraph.addEdge(0, 1);
	expectedGraph.addEdge(1, 2);
	expectedGraph.addEdge(1, 3);
	expectedGraph.addEdge(1, 5);
	expectedGraph.addEdge(2, 3);
	expectedGraph.addEdge(3, 4);
	expectedGraph.addEdge(4, 5);
	expectedGraph.addEdge(4, 6);
	expectedGraph.addEdge(4, 7);
	expectedGraph.addEdge(5, 6);
	expectedGraph.addEdge(6, 7);
	expectedGraph.addEdge(6, 9);
	expectedGraph.addEdge(7, 8);
	expectedGraph.addEdge(8, 9);
	expectedGraph.addTerminal(2);
	expectedGraph.addTerminal(7);
	
	expectedGraph.addArc(1, 10);
	expectedGraph.addArc(0, 11);
	expectedGraph.addArc(2, 11);
	expectedGraph.addArc(3, 11);
	expectedGraph.addArc(5, 11);
	expectedGraph.addArc(1, 12);
	expectedGraph.addArc(2, 12);
	expectedGraph.addArc(4, 12);
	expectedGraph.addArc(3, 13);
	expectedGraph.addArc(5, 13);
	expectedGraph.addArc(6, 13);
	expectedGraph.addArc(7, 13);
	expectedGraph.addArc(1, 14);
	expectedGraph.addArc(4, 14);
	expectedGraph.addArc(6, 14);
	expectedGraph.addArc(4, 15);
	expectedGraph.addArc(5, 15);
	expectedGraph.addArc(7, 15);
	expectedGraph.addArc(9, 15);
	expectedGraph.addArc(7, 16);
	expectedGraph.addArc(9, 16);
	expectedGraph.addArc(6, 17);
	expectedGraph.addArc(8, 17);
	
	expectedGraph.addArc(18, 1);
	expectedGraph.addArc(18, 3);
	expectedGraph.addArc(18, 4);
	expectedGraph.addArc(18, 6);
	expectedGraph.addArc(18, 8);
	expectedGraph.addArc(19, 1);
	expectedGraph.addArc(19, 3);
	expectedGraph.addArc(19, 4);
	expectedGraph.addArc(19, 6);
	expectedGraph.addArc(19, 8);
		
	if (!expectedGraph.equals(decoratedGraph)) {
		cout << "Test error: decorated graph is not equal to expected graph after generation." << endl;
		return 1;
	}
	
	unordered_map<int, int> expectedSinks;
	expectedSinks.insert(make_pair(0, 10));
	expectedSinks.insert(make_pair(1, 11));
	expectedSinks.insert(make_pair(3, 12));
	expectedSinks.insert(make_pair(4, 13));
	expectedSinks.insert(make_pair(5, 14));
	expectedSinks.insert(make_pair(6, 15));
	expectedSinks.insert(make_pair(8, 16));
	expectedSinks.insert(make_pair(9, 17));
	for (auto const& entry : expectedSinks) {
		int vertex = entry.first;
		int expectedSink = entry.second;
		int actualSink = decoratedGraph.getSink(vertex);
		if (actualSink != expectedSink) {
			cout << "Test error: expected sink " << expectedSink << " for vertex " << vertex << " but actually is " << actualSink << "." << endl;
			return 1;
		}
	}
	
	unordered_set<int> expectedSuperSources;
	expectedSuperSources.insert(18);
	expectedSuperSources.insert(19);
	if (decoratedGraph.getSuperSources() != expectedSuperSources) {
		cout << "Test error: incorrect super-sources" << endl;
		return 1;
	}
	
	decoratedGraph.contract(5);
	
	Graph contractedGraph(20);
	contractedGraph.remove(5);
	contractedGraph.remove(14);
	
	contractedGraph.addEdge(0, 1);
	contractedGraph.addEdge(1, 2);
	contractedGraph.addEdge(1, 3);
	contractedGraph.addEdge(1, 4);
	contractedGraph.addEdge(1, 6);
	contractedGraph.addEdge(2, 3);
	contractedGraph.addEdge(3, 4);
	contractedGraph.addEdge(4, 6);
	contractedGraph.addEdge(4, 7);
	contractedGraph.addEdge(6, 7);
	contractedGraph.addEdge(6, 9);
	contractedGraph.addEdge(7, 8);
	contractedGraph.addEdge(8, 9);
	contractedGraph.addTerminal(2);
	contractedGraph.addTerminal(7);
	
	contractedGraph.addArc(1, 10);
	contractedGraph.addArc(0, 11);
	contractedGraph.addArc(2, 11);
	contractedGraph.addArc(3, 11);
	contractedGraph.addArc(4, 11);
	contractedGraph.addArc(6, 11);
	contractedGraph.addArc(1, 12);
	contractedGraph.addArc(2, 12);
	contractedGraph.addArc(4, 12);
	contractedGraph.addArc(1, 13);
	contractedGraph.addArc(3, 13);
	contractedGraph.addArc(6, 13);
	contractedGraph.addArc(7, 13);
	contractedGraph.addArc(1, 15);
	contractedGraph.addArc(4, 15);
	contractedGraph.addArc(7, 15);
	contractedGraph.addArc(9, 15);
	contractedGraph.addArc(7, 16);
	contractedGraph.addArc(9, 16);
	contractedGraph.addArc(6, 17);
	contractedGraph.addArc(8, 17);
	
	contractedGraph.addArc(18, 1);
	contractedGraph.addArc(18, 3);
	contractedGraph.addArc(18, 4);
	contractedGraph.addArc(18, 6);
	contractedGraph.addArc(18, 8);
	contractedGraph.addArc(19, 1);
	contractedGraph.addArc(19, 3);
	contractedGraph.addArc(19, 4);
	contractedGraph.addArc(19, 6);
	contractedGraph.addArc(19, 8);
	
	if (!contractedGraph.equals(decoratedGraph)) {
		cout << "Test error: decorated graph is not equal to expected graph after generation." << endl;
		return 1;
	}
	
	return 0;
}