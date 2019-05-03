#pragma once

#include "matroid.h"
#include "graph.h"
#include "galois.h"

class DualMatroid {
	
	public:
		static Matroid generate(Matroid&, Galois*);
	
	private:
		static void swipeDown(Matroid&, Galois*);
		static void swipeUp(Matroid&, Galois*);
		static void normalize(Matroid&, Galois*);
		static int findPivot(Matroid&, int);
		static void swipeRows(Matroid&, Galois*, int, int, int);
		static Matroid transpose(Matroid&);
};