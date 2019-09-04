#include "stdafx.h"
#include "multiway_cut_kernel.h"

using namespace std;

MultiwayCutKernel::MultiwayCutKernel() {
}

MultiwayCutKernel::~MultiwayCutKernel(){ 
}

Graph MultiwayCutKernel::reduce(Graph& inputGraph) {

	bool contractedVertex = true;
	while(contractedVertex) {
		contractedVertex = contractVertex(inputGraph);
	}


	return inputGraph;
}

//TODO: test multiple contractions?
//TODO: test same vs diff gammoids
//TODO: test adding normal vertices first (does proof protect this?) (adding noise)

bool contractVertex(Graph& inputGraph) {

	//TODO: create matroid over vertices in graph
	//TODO: create gammoids over vertices in graph
	//TODO: create rep set matroid (impl sum matroid?)
	//TODO: call reduction on rep set matroid

	return true;
}








//TODO: contract operation (must have mechanism for graph to know which vertices are still active)
//TODO: must update all graph iteration mechanisms to reflect this (throw error if getOutNeighbor is called for inactive vertex?)