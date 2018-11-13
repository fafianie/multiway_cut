#include "stdafx.h"
#include "graph.h"

int main(int argc, char* argv[]) {
	Graph graph = Graph(100);
	if (!graph.isIndependentSet()) {
		return 1;
	}
	return 0;
}