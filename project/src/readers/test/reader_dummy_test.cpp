#include "stdafx.h"
#include "graph.h"
#include "dfg_reader.h"

using namespace std;

int main(int argc, char* argv[]) {

	Graph graph = DFGReader::read("", "");

	if (!graph.isIndependentSet()) {
		cout << "dependency test failed";
		return 1;
	}
	
	cout << "deleted" << endl;
	return 0;
}