#include "stdafx.h"
#include "carryless_multiplier_galois.h"
#include "naive_galois.h"
#include "matroid.h"
#include "gauss.h"
#include "dual_matroid.h"
#include "gammoid.h"
#include "transversal_matroid.h"
#include "powers.cpp"
#include "independent_set.h"

using namespace std;

struct pair_hash {
    inline size_t operator()(const pair<int,int> & v) const {
        return v.first * 31 + v.second;
    }
};

bool cliqueTestPasses() { 
	Galois* galois = new NaiveGalois(8);
	for (int numberOfSources = 2; numberOfSources < 11; numberOfSources++) {
		Graph graph(numberOfSources * numberOfSources);
		vector<int> sinks;
		unordered_set<int> sources;
		for (int source = 0; source < numberOfSources; source++) {
			sources.insert(source * numberOfSources);
			sinks.push_back(source * numberOfSources + numberOfSources - 1);
		}
		for (int u : graph.getVertices()) {
			for (int v : graph.getVertices()) {
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
	int numberOfSources = 5;
	int pathLength = 5;
	int repetitions = 100;
    int vertices = 50;
    int edges = 200;

	Galois* galois = new CarrylessMultiplierGalois;
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
	int repetitions = 100;
	int paths = 5;
	int funnelSize = paths - 1;
	int edges = 150;
	int pathLength = 5;
	int surplus = 25;
	int vertices = paths * pathLength * 2 + funnelSize + surplus;
	int minSideSize = paths * pathLength;
	int maxSideSize = vertices - (funnelSize + minSideSize);
	Galois* galois = new CarrylessMultiplierGalois();
	
	std::mt19937 randomGenerator;
	std::uniform_int_distribution<int> sizeDistribution(minSideSize, maxSideSize);
	std::uniform_int_distribution<int> funnelDistribution(0, funnelSize - 1);
	
	for (int repetition = 0; repetition < repetitions; repetition++) {
		Graph graph(vertices);
		unordered_set<int> sources;
		vector<int> sinks;
	
		int leftStart = 0;
		int leftEnd = sizeDistribution(randomGenerator);
		int rightStart = leftEnd + funnelSize;
		int rightEnd = vertices;

		for (int path = 0; path < paths; path++) {
			int offset = path * pathLength;
			for (int pathVertex = 1; pathVertex < pathLength; pathVertex++) {
				int leftPathVertex = pathVertex + offset;
				int rightPathVertex = rightStart + pathVertex + offset;
				graph.addEdge(leftPathVertex, leftPathVertex - 1);
				graph.addEdge(rightPathVertex, rightPathVertex - 1);
				edges -= 2;
			}
			sinks.push_back(offset);
			sources.insert(rightStart + offset + pathLength - 1);
		}
	
		for (int funnelIndex = 0; funnelIndex < funnelSize; funnelIndex++) {
			int offset = funnelIndex * pathLength;
			int leftPathVertex = offset + pathLength - 1;
			int rightPathVertex = rightStart + offset;
			int funnelVertex = leftEnd + funnelIndex;
			graph.addEdge(leftPathVertex, funnelVertex);
			graph.addEdge(funnelVertex, rightPathVertex);
			edges -= 2;
		}
	
		int leftPathVertex = paths * pathLength - 1;
		int rightPathVertex = rightStart + (paths - 1)* pathLength;
		int funnelVertex = leftEnd + funnelDistribution(randomGenerator);
		graph.addEdge(leftPathVertex, funnelVertex);
		graph.addEdge(funnelVertex, rightPathVertex);
		edges -= 2;
	
		unordered_set<pair<int, int>, pair_hash> edgeCandidates;
		for (int u = 0; u < leftEnd + funnelSize; u++) {
			for (int v = u + 1; v < leftEnd; v++) {
				pair<int, int> edgeCandidate(u, v);
				edgeCandidates.insert(edgeCandidate);
			}
		}
		for (int u = rightStart - funnelSize; u < vertices; u++) {
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
		}
		Matroid gammoid = Gammoid::generate(graph, galois, sources);
		if (gammoid.isIndependent(sinks, galois)) {
			cout << "Test failure: Paths with funnel and noise are independent." << endl;
			return false;
		}
	}
	return true;
}

bool directedTestPasses() {
	Graph graph(3);
	graph.addArc(0, 1);
	graph.addArc(1, 2);
	unordered_set<int> sources;
	sources.insert(1);
	vector<int> sinks;
	Galois* galois = new CarrylessMultiplierGalois();
	Matroid gammoid = Gammoid::generate(graph, galois, sources);
	
	sinks.push_back(0);
	if (gammoid.isIndependent(sinks, galois)) {
		cout << "Test failure: InNeighbor is independent." << endl;
		return false;
	}
	sinks.clear();
	sinks.push_back(1);
	if (!gammoid.isIndependent(sinks, galois)) {
		cout << "Test failure: Source is not independent." << endl;
		return false;
	}
	sinks.clear();
	sinks.push_back(2);
	if (!gammoid.isIndependent(sinks, galois)) {
		cout << "Test failure: OutNeighbor is not independent." << endl;
		return false;
	}

	return true;
}

int main(int argc, char* argv[]) {
	
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
	if (!directedTestPasses()) {
		return 1;
	}
	return 0;
}
