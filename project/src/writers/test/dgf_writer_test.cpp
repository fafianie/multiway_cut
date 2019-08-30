#include "stdafx.h"
#include "graph.h"
#include "dgf_writer.h"
#include "dgf_reader.h"

using namespace std;

int main(int argc, char* argv[]) {	
	Graph input = DGFReader::read("../../resources/test/readers/", "reader_test");
	DGFWriter::write(input,
					"../../resources/test/writers/", 
					"writer_test", 
					"This graph is used for the execution of writer_test");
	Graph output = DGFReader::read("../../resources/test/writers/", "writer_test");
	if (!input.equals(output)) {
		cout << "Test error: written graph does not match read graph." << endl;
		return 1;
	}
	return 0;
}