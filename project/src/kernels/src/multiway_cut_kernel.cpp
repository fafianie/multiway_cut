#include "stdafx.h"
#include "multiway_cut_kernel.h"
#include "carryless_multiplier_galois.h"
#include "matroid.h"
#include "uniform_matroid.h"
#include "gammoid.h"
#include "independent_set.h"

using namespace std;

Graph MultiwayCutKernel::reduce(Graph& inputGraph, int k, int superSources, int layers, Galois* galois) {

	//DecoratedGraph decoratedGraph(inputGraph, k);
	Matroid uniformMatroid = UniformMatroid::generate(inputGraph.getVertices().size(), k, galois);
	unordered_set<int> candidateVertices;
	unordered_set<int> otherVertices;
	vector<DecoratedGraph> decoratedGraphs;
	
	for (int terminal : inputGraph.getTerminals()) {
		otherVertices.insert(terminal);
		DecoratedGraph decoratedGraph(inputGraph, superSources);
		decoratedGraph.remove(terminal);
		for (int outNeighbor : inputGraph.getOutNeighbors(terminal)) {
			otherVertices.insert(outNeighbor);
			decoratedGraph.remove(outNeighbor);
		}
		decoratedGraphs.push_back(decoratedGraph);
	}
	
	//cout << "created graphs" << endl;
	for (int vertex : inputGraph.getVertices()) {
		if (otherVertices.find(vertex) == otherVertices.end()) {
			candidateVertices.insert(vertex);
		}
	}

	//cout << "start main loop" << endl;
	bool contractedVertex = true;
	while(contractedVertex) {
		contractedVertex = contractVertex(inputGraph, decoratedGraphs, uniformMatroid, candidateVertices, otherVertices, galois);
	}
	return inputGraph;
}

//TODO: test multiple contractions
//TODO: test same vs diff gammoids

bool MultiwayCutKernel::contractVertex(Graph& inputGraph, vector<DecoratedGraph>& decoratedGraphs, Matroid& uniformMatroid, unordered_set<int>& candidateVertices, unordered_set<int>& otherVertices, Galois* galois) {

	int sumRank = uniformMatroid.getRank();
	//cout << "uniform" << endl;
	//uniformMatroid.display(galois);
	vector<Matroid> gammoids;
	//cout << "creating gammoids" << endl;
	for (DecoratedGraph& decoratedGraph : decoratedGraphs) {
		Matroid gammoid = Gammoid::generate(decoratedGraph, galois, decoratedGraph.getSuperSources()); //TODO: contract N[T]?
		gammoids.push_back(gammoid);
		sumRank *= gammoid.getRank();
		//cout << "gammoid" << endl;
		//gammoid.display(galois);
	}
	//cout << "done creating gammoids" << endl;
	IndependentSet independentSet(sumRank, galois);
	
	/*for (int otherVertex : otherVertices) { careful not to try and make tuples for elements that do not exist
		vector<uint64_t> column = sumColumn(otherVertex, decoratedGraph.getSink(otherVertex), uniformMatroid, gammoids, galois);
		independentSet.addColumn(column);
	}*/
	
	unordered_set<int> candidatesCopy;
	for (int candidateVertex : candidateVertices) {
		candidatesCopy.insert(candidateVertex);
	}
	
	//cout << "looking for candidates" << endl;
	for (int candidateVertex : candidatesCopy) {
		vector<uint64_t> column = sumColumn(candidateVertex, decoratedGraphs[0].getSink(candidateVertex), uniformMatroid, gammoids, galois);
		//cout << endl << "adding column: " << endl;
		/*for (auto const& field : column) {
			cout << galois -> toString(field) << endl;
		}*/
		
		
		if (independentSet.addColumn(column)) {
			//cout << "column was independent" << endl;
			continue;
		}
		//cout << "contracting graphs" << endl;
		inputGraph.contract(candidateVertex);
		for (DecoratedGraph& decoratedGraph : decoratedGraphs) {
			decoratedGraph.contract(candidateVertex);
		}
		cout << "contracted " << candidateVertex << endl;
		cout << "remaining " << candidateVertices.size() -1 << " with rank " << sumRank << endl;
		candidateVertices.erase(candidateVertex); //concurrent modification?
		//cout << "found candidates" << endl;
		return true;
	}
	return false;
}

vector<uint64_t> MultiwayCutKernel::sumColumn(int vertex, int sinkCopy, Matroid& uniformMatroid, vector<Matroid>& gammoids, Galois* galois) {
	//cout << "creating column" << endl;
	vector<uint64_t>& uniformColumn = uniformMatroid.getElementColumn(vertex);
	/*cout << endl << "uniform matroid column: " << endl;
	for (auto const& field : uniformColumn) {
		cout << galois -> toString(field) << endl;
	}*/
	stack<vector<uint64_t>> gammoidColumns;
	for (Matroid& gammoid : gammoids) {
		vector<uint64_t>& gammoidColumn = gammoid.getElementColumn(sinkCopy);
		/*cout << endl << "gammoid column: " << endl;
		for (auto const& field : gammoidColumn) {
			cout << galois -> toString(field) << endl;
		}*/
		gammoidColumns.push(gammoidColumn);
	}
	return multiplyColumns(uniformColumn, gammoidColumns, galois);
}

vector<uint64_t> MultiwayCutKernel::multiplyColumns(vector<uint64_t>& resultColumn, stack<vector<uint64_t>>& columns, Galois* galois) { 
	if (columns.empty()) {
		return resultColumn;
	}
	vector<uint64_t> result;
	vector<uint64_t> nextColumn = columns.top();
	columns.pop();
	
	for (uint64_t leftValue : resultColumn) {
		for (uint64_t rightValue : nextColumn) {
			uint64_t product = galois -> multiply(leftValue, rightValue);
			result.push_back(product);
		}
	}
	return multiplyColumns(result, columns, galois);
}