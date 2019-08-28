#include "stdafx.h"
#include "naive_galois.h"
#include "powers.cpp"

using namespace std;

int main(int argc, char* argv[]) {
	
	string var1(argv[1]);
	string var2(argv[2]);
	uint64_t arg1 = 0L;
	uint64_t arg2 = 0L;
	int indexCounter = 0;
	for (int i = var1.length()-1; i >= 0; i--) {
		if (var1[i] == '1') {
			arg1 ^= pw[indexCounter];
		}
		indexCounter++;
	}
	indexCounter = 0;
	for (int i = var2.length()-1; i >= 0; i--) {
		if (var2[i] == '1') {
			arg2 ^= pw[indexCounter];
		}
		indexCounter++;
	}
	Galois* galois = new NaiveGalois(8);
	uint64_t result = galois -> divide(arg1, arg2);
	
	
	cout << galois -> toString(arg1) << " / " << galois -> toString(arg2) << " = " << galois -> toString(result) << endl;
	return 0;
}