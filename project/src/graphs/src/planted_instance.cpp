#include "stdafx.h"
#include "planted_instance.h"

using namespace std;

PlantedInstance::PlantedInstance(const int initVertices,
								 const int clusters,
								 const int terminals,
								 const int edges,
								 const int hubSize,
								 const int hubEdges,
								 const int budget) : Graph(initVertices) {
	
	int edgeBudget = edges;
	//TODO: better rounding
	int clusterSize = (initVertices - hubSize) / clusters;
	
	//CREATE HUB EDGES
	vector<tuple<int, int>> hubEdgeCandidates;
	createEdgeCandidates(hubEdgeCandidates, 0, hubSize);
	addEdges(hubEdgeCandidates, hubEdges);
	edgeBudget -= hubEdges;
	
	//CLUSTERS
	int offset = hubSize;
	vector<tuple<int, int>> edgeCandidates;
	for (int cluster = 0; cluster < clusters - 1; cluster++) {
		createSpanningTree(offset, offset + clusterSize);
		edgeBudget -= (clusterSize - 1);
		createEdgeCandidates(edgeCandidates, offset, offset + clusterSize);
		createClusterToHubCandidates(edgeCandidates, offset, offset + clusterSize, budget);
		
		offset += clusterSize;
		
	
	}
	
	//LAST CLUSTER
	createSpanningTree(offset, initVertices);
	edgeBudget -= ((initVertices - offset) - 1);
	createEdgeCandidates(edgeCandidates, offset, initVertices);
	createClusterToHubCandidates(edgeCandidates, offset, initVertices, budget);
	addEdges(edgeCandidates, edgeBudget);
	
}

PlantedInstance::~PlantedInstance() {
	
}

void PlantedInstance::createEdgeCandidates(vector<tuple<int, int>>& candidates, 
										   int firstVertex, 
										   int lastVertex) {
	int added = 0;
	for (int left = firstVertex; left < lastVertex; left++) {
		for (int right = left + 1; right < lastVertex; right++) {
			if (!isOutNeighbor(left, right)) {
				candidates.push_back(make_tuple(left, right));
				added++;
			}
		}
	}
}

void PlantedInstance::createClusterToHubCandidates(vector<tuple<int, int>>& candidates, 
								  int firstVertex, 
								  int lastVertex,
								  int budget) {
	for (int clusterVertex = firstVertex; clusterVertex < lastVertex; clusterVertex++) {
		for (int solutionVertex = 0; solutionVertex < budget; solutionVertex++) {
			candidates.push_back(make_tuple(clusterVertex, solutionVertex));
		}
	}
}

void PlantedInstance::addEdges(vector<tuple<int, int>>& candidates, int amount) {
	random_shuffle(candidates.begin(), candidates.end());
	for (int edgeIndex = 0; edgeIndex < amount; edgeIndex++) {
		tuple<int, int> edge = candidates[edgeIndex];
		addEdge(get<0>(edge), get<1>(edge));
	}
}

void PlantedInstance::createSpanningTree(int firstVertex, int lastVertex) {
	for (int vertex = firstVertex + 1; vertex < lastVertex; vertex++) {
			uniform_int_distribution<> distribution(firstVertex, vertex - 1);
			int anchor = distribution(randomGenerator);
			addEdge(vertex, anchor);
		}
}