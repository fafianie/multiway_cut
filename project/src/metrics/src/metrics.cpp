#include "stdafx.h"
#include "metrics.h"

using namespace std;

Metrics::Metrics() : numberOfEntries(0) {
	
}

Metrics::~Metrics() {
}

int Metrics::getEntries() {
	return numberOfEntries;
}

vector<string> Metrics::getHeaders() {
	return headers;
}

void Metrics::addEntry(map<string, string>& entry) {
	entries.push_back(entry);
	for (auto const& field : entry) {
		string header = field.first;
		if (uniqueHeaders.find(header) == uniqueHeaders.end()) {
			headers.push_back(header);
			uniqueHeaders.insert(header);
		}
	}
	numberOfEntries++;
}

vector<string> Metrics::getEntry(int index) {
	vector<string> result;
	map<string, string> entry = entries[index];
	for (string header : headers) {
		string field = "";
		if (entry.count(header) > 0) {
			field = entry[header];
		}
		result.push_back(field);
	}
	return result;
}