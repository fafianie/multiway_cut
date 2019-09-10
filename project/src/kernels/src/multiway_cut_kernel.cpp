#include "stdafx.h"
#include "multiway_cut_kernel.h"
#include "carryless_multiplier_galois.h"
#include "matroid.h"
#include "uniform_matroid.h"
#include "gammoid.h"
#include "independent_set.h"

using namespace std;

MultiwayCutKernel::MultiwayCutKernel() {
}

MultiwayCutKernel::~MultiwayCutKernel(){  //TODO: make static
}

Graph MultiwayCutKernel::reduce(Graph& inputGraph, int k, Galois* galois) {

	DecoratedGraph decoratedGraph(inputGraph, k);
	Matroid uniformMatroid = UniformMatroid::generate(inputGraph.getVertices().size(), k, galois);
	unordered_set<int> candidateVertices;
	unordered_set<int> otherVertices;
	
	for (int terminal : inputGraph.getTerminals()) {
		otherVertices.insert(terminal);
		for (int outNeighbor : inputGraph.getOutNeighbors(terminal)) {
			otherVertices.insert(outNeighbor);
		}
	}
	for (int vertex : inputGraph.getVertices()) {
		if (otherVertices.find(vertex) != otherVertices.end()) {
			candidateVertices.insert(vertex);
		}
	}
	
	// =>
	//TODO: create multiple decoratedGraphs, one for each layer, and delete N(t_i) in each ...!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// =>
	
	
	bool contractedVertex = true;
	while(contractedVertex) {
		contractedVertex = contractVertex(inputGraph, decoratedGraph, uniformMatroid, candidateVertices, otherVertices, galois);
	}
	
	
	
	
	//candidates for contraction: any vertex that is not in N[T]
	//to add to matroid: any vertex not in T
	//TODO: precompute these sets
	//TODO: precompute uniform matroid
	//TODO: need k + 1 paths, so k + 1 supersources, but still need to block all of N[T]? (may need to do matroid contraction...)

	return inputGraph;
}

//TODO: test multiple contractions?
//TODO: test same vs diff gammoids

bool MultiwayCutKernel::contractVertex(Graph& inputGraph, DecoratedGraph& decoratedGraph, Matroid& uniformMatroid, unordered_set<int>& candidateVertices, unordered_set<int>& otherVertices, Galois* galois) {

	int sumRank = uniformMatroid.getRank();
	vector<Matroid> gammoids;
	for (int terminal : inputGraph.getTerminals()) {
		Matroid gammoid = Gammoid::generate(decoratedGraph, galois, decoratedGraph.getSuperSources()); //TODO: contract N[T]?
		gammoids.push_back(gammoid);
		sumRank *= gammoid.getRank();
	}
	IndependentSet independentSet(sumRank, galois);
	
	for (int otherVertex : otherVertices) {
		vector<uint64_t> column = sumColumn(otherVertex, decoratedGraph.getSink(otherVertex), uniformMatroid, gammoids, galois);
		independentSet.addColumn(column);
	}
	
	for (int candidateVertex : candidateVertices) {
		vector<uint64_t> column = sumColumn(candidateVertex, decoratedGraph.getSink(candidateVertex), uniformMatroid, gammoids, galois);
		if (independentSet.addColumn(column)) {
			continue;
		}
		inputGraph.contract(candidateVertex);
		decoratedGraph.contract(candidateVertex);
		candidateVertices.erase(candidateVertex); //concurrent modification?
		return true;
	}
	return false;
}

vector<uint64_t> MultiwayCutKernel::sumColumn(int vertex, int sinkCopy, Matroid& uniformMatroid, vector<Matroid>& gammoids, Galois* galois) {
	vector<uint64_t>& uniformColumn = uniformMatroid.getElementColumn(vertex);
	stack<vector<uint64_t>> gammoidColumns;
	for (Matroid& gammoid : gammoids) {
		gammoidColumns.push(gammoid.getElementColumn(sinkCopy));
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