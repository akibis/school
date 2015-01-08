/**
@File: uniformDist.cpp
@Author: Aleksandr Kibis
@Date: 12/12/2013
*/

#include "uniformDist.h"

using namespace std;

// START QUESTION #1 FUNCTIONS
// Generate random number between 0 and 1
double getNumber(){
	random_device engine;
	uniform_real_distribution<double> dist(0, 1);
	return dist(engine);
}

// Build array for part A
double* buildSampleA(int size){
	double* arrayA = new double[size];
	for (int i=0; i<size; i++){
		double element = 0.0;
		int count = 0;	// initialize counter, counts amount of adds
		while (element < 1.0){
			element += getNumber();
			count++; // increment count with every loop
			if (element > 1.0)
				arrayA[i] = count; // input number of adds into array
		}
		
	}
	return arrayA;
}

// Build array for part B
double* buildSampleB(int size){
	double* arrayB = new double[size];
	double first = getNumber();
	double second = getNumber();
	
	for (int i=0; i<size; i++){
		int count = 1;
		while (first < second){ // test xn < xn+1
			++count;
			first = second;
			second = getNumber();		
		}
		arrayB[i] = count; // assign count number to array of sample size
		if  (first >= second){ // pick new numbers if first is greater
			first = getNumber();
			second = getNumber();
		}
	}
	return arrayB;
}

// Get mean of array
double getMean(int size, double* array){
	double sum = 0.0;
	for (int i=0; i < size; i++){
		sum += array[i];
	}
	return sum / size;
}
// END QUESTION #1 FUNCTIONS


















