#pragma once

#include "metrics.h"

class MetricsWriter {

	public:
		static void write(Metrics&, std::string, std::string, std::string);
};