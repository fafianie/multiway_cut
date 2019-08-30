#include "stdafx.h"
#include "metrics.h"
#include "metrics_writer.h"

using namespace std;

int main(int argc, char* argv[]) {	

	string path = "../../resources/test/writers/";
	string filename = "writer_test";
	string extension = ".csv";
	string comment = "This file is used for the execution of metrics_writer_test";
	
	Metrics metrics;
	map<string, string> firstEntry;
	firstEntry.insert(make_pair("input graph", "graphA"));
	firstEntry.insert(make_pair("running time", "100ms"));
	map<string, string> secondEntry;
	secondEntry.insert(make_pair("input graph", "graph B"));
	secondEntry.insert(make_pair("vertices", "100"));
	map<string, string> thirdEntry;
	thirdEntry.insert(make_pair("running time", "200ms"));
	thirdEntry.insert(make_pair("edges", "200"));
	metrics.addEntry(firstEntry);
	metrics.addEntry(secondEntry);
	metrics.addEntry(thirdEntry);
	MetricsWriter::write(metrics, path, filename, comment);

	ifstream infile(path + filename + extension);
	string line;
	getline(infile, line);
	if (line != "This file is used for the execution of metrics_writer_test") {
		return 1;
	}
	getline(infile, line);
	if (line != "input graph,running time,vertices,edges") {
		return 1;
	}
	getline(infile, line);
	if (line != "graphA,100ms,,") {
		return 1;
	}
	getline(infile, line);
	if (line != "graph B,,100,") {
		return 1;
	}
	getline(infile, line);
	if (line != ",200ms,,200") {
		return 1;
	}
	return 0;
}