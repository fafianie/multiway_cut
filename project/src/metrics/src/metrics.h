#pragma once

#include "stdafx.h"

class Metrics {

	public:
		Metrics();
		~Metrics();
		int getEntries();
		std::vector<std::string> getHeaders();
		void addEntry(std::map<std::string, std::string>& entry);
		std::vector<std::string> getEntry(int);

	private:
		std::map<std::string, int> headerIndex;
		std::vector<std::string> headers;
		std::unordered_set<std::string> uniqueHeaders;
		std::vector<std::map<std::string, std::string>> entries;
		int numberOfEntries;
};