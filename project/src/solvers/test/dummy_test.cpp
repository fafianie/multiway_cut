#include "stdafx.h"
#include "graph.h"
#include "planted_instance.h"

using namespace std;

int main(int argc, char* argv[]) {
	
	Graph* planted = new PlantedInstance(100, 7, 5, 300 ,10, 20, 4);
	delete planted;
	
	
	
	
	
	return 0;
}