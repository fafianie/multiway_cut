#include "stdafx.h"
#include <thread>

using namespace std;

int main(int argc, char* argv[]) { 
	
	for (int i = 0; i < 20; i++) {
	
		this_thread::sleep_for(std::chrono::milliseconds(1000));
		cout << "slept for " << i << " seconds" << endl;
	}
	
	return 0;
}