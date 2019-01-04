#include "stdafx.h"
#include "graph.h"
#include "planted_instance.h"

int main(int argc, char* argv[]) {
	Graph graph = Graph(100);
	if (!graph.isIndependentSet()) {
		return 1;
	}
	
	Graph* planted = new PlantedInstance(100, 7, 5, 300 ,10, 20, 4);
	delete planted;
	
	return 0;
}