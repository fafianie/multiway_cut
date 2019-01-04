#pragma once

#include "stdafx.h"
#include "graph.h"

class PlantedInstance : public Graph {
	
	public: 
		PlantedInstance(const int, const int, const int, const int, const int, const int, const int);
		~PlantedInstance();
	
	private:
		void createEdgeCandidates(std::vector<std::tuple<int, int>>&, int, int);
		void createClusterToHubCandidates(std::vector<std::tuple<int, int>>&, int, int, int);
		void addEdges(std::vector<std::tuple<int, int>>&, int);
		void createSpanningTree(int, int);
		std::mt19937 randomGenerator;
};