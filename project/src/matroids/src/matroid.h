#pragma once

#include "stdafx.h"

class Matroid {
	
	public:
		Matroid(uint64_t **representation);
		~Matroid();
	
		void swapElements(int, int);
	
	private:
		uint64_t **representation;
		uint64_t *aliases;
}