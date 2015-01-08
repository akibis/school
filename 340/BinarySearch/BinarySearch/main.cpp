#include "exceptions.h"
#include <iostream>

using namespace std;

int main(){
	int size = 10;
	try {
		int* newArray = new int[size - 20];
	}
	catch (bad_alloc & e) {
		cerr << e.what();
	}


	return 0;
}