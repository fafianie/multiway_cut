#include "stdafx.h"
#include "carryless_multiplier_galois.h"
#include "naive_galois.h"
#include "matroid.h"
#include "gauss.h"
#include "dual_matroid.h"
#include "gammoid.h"
#include "transversal_matroid.h"
#include "powers.cpp"

using namespace std;

struct pair_hash {
    inline size_t operator()(const pair<int,int> & v) const {
        return v.first * 31 + v.second;
    }
};

bool cliqueTestPasses() { 
	Galois* galois = new CarrylessMultiplierGalois();
	for (int numberOfSources = 2; numberOfSources < 11; numberOfSources++) {
		Graph graph(numberOfSources * numberOfSources);
		vector<int> sinks;
		unordered_set<int> sources;
		for (int source = 0; source < numberOfSources; source++) {
			sources.insert(source * numberOfSources);
			sinks.push_back(source * numberOfSources + numberOfSources - 1);
		}
		for (int u = 0; u < graph.getVertices(); u++) {
			for (int v = u; v < graph.getVertices(); v++) {
				graph.addEdge(u, v);
			}
		}
		Matroid gammoid = Gammoid::generate(graph, galois, sources);
		if (!gammoid.isIndependent(sinks, galois)) {
				cout << "Test failure: Clique with size " << numberOfSources << " is not independent." << endl;
				return false;
		}
	}
	return true;
}

bool pathsWithNoiseTestPasses() {
	int numberOfSources = 5; //TODO: make global const ints
	int pathLength = 5;
	int repetitions = 100;
    int vertices = 50;
    int edges = 200;

	Galois* galois = new CarrylessMultiplierGalois();
	for (int repetition = 0; repetition < repetitions; repetition++) {
		Graph graph(vertices);
		vector<int> aliases;
		for (int vertex = 0; vertex < vertices; vertex++) {
			aliases.push_back(vertex);
		}
		random_shuffle(aliases.begin(), aliases.end());
		unordered_set<int> sources;
		vector<int> sinks;
		unordered_set<pair<int, int>, pair_hash> edgeCandidates;
		for (int u = 0; u < vertices; u++) {
			for (int v = u + 1; v < vertices; v++) {
				pair<int, int> edgeCandidate(u, v);
				edgeCandidates.insert(edgeCandidate);
			}
		}	
		int offset = 0;
		for (int source = 0; source < numberOfSources; source++) {
			sources.insert(aliases.at(offset));
			for (int pathVertex = 1; pathVertex < pathLength; pathVertex++) {
				int index = pathVertex + offset;
				int currentVertex = aliases.at(index);
				int previousVertex = aliases.at(index - 1);
				graph.addEdge(previousVertex, currentVertex);
				pair<int, int> blockedCandidate(index - 1, index);
				edgeCandidates.erase(edgeCandidates.find(blockedCandidate));
			}
			offset += pathLength;
			sinks.push_back(aliases.at(offset - 1));
		}
		
		vector<pair<int, int>> shuffledEdges;
		for (auto edgeCandidate : edgeCandidates) {
			shuffledEdges.push_back(edgeCandidate);
		}
		random_shuffle(shuffledEdges.begin(), shuffledEdges.end());
		for (int edge = 0; edge < edges; edge++) {
			pair<int, int> edgeCandidate = shuffledEdges.at(edge);
			int u = aliases.at(edgeCandidate.first);
			int v = aliases.at(edgeCandidate.second);
			graph.addEdge(u, v);
		}
		Matroid gammoid = Gammoid::generate(graph, galois, sources);
		if (!gammoid.isIndependent(sinks, galois)) {
			cout << "Test failure: Paths with noise are not independent." << endl;
			return false;
		}
	}
	return true;
}

bool independentSetTestPasses() { 
	int elements = 6;
	int numberOfSources = 3;
	Galois* galois = new CarrylessMultiplierGalois();
	Graph graph(elements);
	unordered_set<int> sources;
	vector<int> sinks;
	for (int vertex = 0; vertex < numberOfSources; vertex++) {
		sources.insert(vertex);
	}
	Matroid gammoid = Gammoid::generate(graph, galois, sources);
	for (int candidateSeed = 0; candidateSeed < pw[elements]; candidateSeed++) {
		vector<int> sinks;
		for (int elementIndex = 0; elementIndex < elements; elementIndex++) {
			if (candidateSeed & pw[elementIndex]) {
				sinks.push_back(elementIndex);
			}
		}
		bool independent = gammoid.isIndependent(sinks, galois);
		if (candidateSeed > pwm1[numberOfSources] == independent) { 
			if (independent) {
				cout << "Test failure: independent while containing a non-sink" << endl;
			} else {
				cout << "Test failure: not independent while only containing sinks" << endl;
			}
			return false;
		}
	}
	return true;
}

bool funnelTestPasses() {
	int paths = 5;
	int funnelSize = paths - 1;
	int vertices = 100; //must have at least path*length*2 + funnel vertices = 54
	int edges = 300;
	int pathLength = 5; //length on both sides
	
	Galois* galois = new CarrylessMultiplierGalois();
	Graph graph(vertices);
	unordered_set<int> sources;
	vector<int> sinks;
	
	//TODO: identify left side, right side, and funnel...
	//funnel is fixed size
	//left side requires at least *paths* many vertices
	//right side requires at least *paths* many vertices
	//randomly decide splitting pointer
	//but also ensure enough vertices are on either side to make the paths (half half)
	
	int minSideSize = paths * pathLength;
	int maxSideSize = vertices - (funnelSize + minSideSize);
	std::mt19937 randomGenerator;

	std::uniform_int_distribution<int> distribution(minSideSize, maxSideSize); // uniform, unbiased
	int leftStart = 0;
	int leftEnd = distribution(randomGenerator);
	int rightStart = leftEnd + funnelSize;
	int rightEnd = vertices;
	cout << "funnelSize: " << funnelSize << endl;
	cout << "leftEnd: " << leftEnd << endl;
	cout << "rightStart: " << rightStart << endl;
	//todo link paths
	for (int path = 0; path < paths; path++) {
		int offset = path * pathLength;
		for (int pathVertex = 1; pathVertex < pathLength; pathVertex++) {
			int leftPathVertex = pathVertex + offset;
			int rightPathVertex = rightStart + pathVertex + offset;
			cout << "left: " << leftPathVertex << endl;
			cout << "right: " << rightPathVertex << endl;
			graph.addEdge(leftPathVertex, leftPathVertex - 1);
			graph.addEdge(rightPathVertex, rightPathVertex - 1);
			edges -= 2;
		
			//output edges to make sure they are correct
			//add edge between this and previous
			//update offset...
		}
		//connect to funnel (BUT SKIP THE LAST ONE OR THIS APPROACH FAILS!!!)
		/*int leftPathVertex = offset;
		int rightPathVertex = rightStart + offset;
		int funnelVertex = leftEnd + path;
		cout << "*** adding funnel" << endl;
		cout << "leftPathVertex: " << leftPathVertex << endl;
		cout << "funnelVertex: " << funnelVertex << endl;
		cout << "rightPathVertex: " << rightPathVertex << endl;
		cout << "***" << endl;
		graph.addEdge(leftPathVertex, funnelVertex);
		graph.addEdge(funnelVertex, rightPathVertex);
		edges -= 2;*/
		
		//add sinks
		sinks.push_back(offset);
		cout << "ADDED SOURCE: " << offset << endl;
		//add sources
		sources.insert(rightStart + offset + pathLength);
		cout << "ADDED SINK: " << rightStart + offset + pathLength << endl; 
	}
	
	for (int funnelIndex = 0; funnelIndex < funnelSize; funnelIndex++) {
		int offset = funnelIndex * pathLength;
		int leftPathVertex = offset;
		int rightPathVertex = rightStart + offset;
		int funnelVertex = leftEnd + funnelIndex;
		cout << "*** adding funnel" << endl;
		cout << "leftPathVertex: " << leftPathVertex << endl;
		cout << "funnelVertex: " << funnelVertex << endl;
		cout << "rightPathVertex: " << rightPathVertex << endl;
		cout << "***" << endl;
		graph.addEdge(leftPathVertex, funnelVertex);
		graph.addEdge(funnelVertex, rightPathVertex);
		edges -= 2;
	}
	
	
	
	
	//add edge candidates
	//must be contained all on one side (including funnel)
	/*unordered_set<pair<int, int>, pair_hash> edgeCandidates;
	for (int u = 0; u < rightStart; u++) {
		for (int v = u + 1; v < rightStart; v++) {
			pair<int, int> edgeCandidate(u, v);
			edgeCandidates.insert(edgeCandidate);
		}
	}
	for (int u = leftEnd; u < vertices; u++) {
		for (int v = u + 1; v < vertices; v++) {
			pair<int, int> edgeCandidate(u, v);
			edgeCandidates.insert(edgeCandidate);
		}
	}
	vector<pair<int, int>> shuffledEdges;
	for (auto edgeCandidate : edgeCandidates) {
		shuffledEdges.push_back(edgeCandidate);
	}
	random_shuffle(shuffledEdges.begin(), shuffledEdges.end());
	for (int edge = 0; edge < edges; edge++) {
		pair<int, int> edgeCandidate = shuffledEdges.at(edge);
		int u = edgeCandidate.first;
		int v = edgeCandidate.second;
		graph.addEdge(u, v);
	}*/
	
	Matroid gammoid = Gammoid::generate(graph, galois, sources);
	if (gammoid.isIndependent(sinks, galois)) {
		cout << "Test failure: Paths with funnel and noise are independent." << endl;
		return false;
	}
	
	
	
	
	//connect nine paths evenly, last one randomly intersecting
	
	
	
	
	
	
	
	//todo: add repetitions

	
	
	
	
	//negative cases: add artificial cuts (funnels)
	//create k-1 size crossing
	//split remainder of graph in two parts
	//make paths, with ends in each part, intersecting the crossing
	//add extra edges (but don't connect parts outside of crossing)
	
	

	return true;
}

int main(int argc, char* argv[]) {
	
	Galois* galoisX = new CarrylessMultiplierGalois();
	
	if (!cliqueTestPasses()) {
		return 1;
	}
	if (!pathsWithNoiseTestPasses()) {
		return 1;
	}
	if (!independentSetTestPasses()) {
		return 1;
	}
	if (!funnelTestPasses()) {
		return 1;
	}
	return 0;
}
