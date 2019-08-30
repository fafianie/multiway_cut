#include "stdafx.h"
#include "metrics.h"
#include "metrics_writer.h"

using namespace std;

static const string extension = ".csv";

void MetricsWriter::write(Metrics& metrics, string path, string filename, string comment) {
	ofstream outfile(path + filename + extension);
	outfile << comment << endl;
	bool writeComma = false;
	for (string header : metrics.getHeaders()) {
		if (writeComma) {
			outfile << ",";
		}
		outfile << header;
		writeComma = true;
	}
	for (int i = 0; i < metrics.getEntries(); i++) {
		outfile << endl;
		writeComma = false;
		for (string field : metrics.getEntry(i)) {
			if (writeComma) {
				outfile << ",";
			}
			outfile << field;
			writeComma = true;
		}
	}
	outfile.close();
}