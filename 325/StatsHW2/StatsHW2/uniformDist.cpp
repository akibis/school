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
	double* array = new double[size];
	
	for (int i=0; i<size; i++){
		double element = 0.0;
		while (element < 1.0)
			element += getNumber();
		array[i] = element;
	}
	return array;
}

// Build array for part B
double* buildSampleB(int size){
	double* array = new double[size];
	double first = getNumber();
	double second = getNumber();
	
	for (int i=0; i<size; i++){
		while (first > second){
			second = first;
			first = getNumber();
		}
		array[i] = first;
	}
	return array;
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


// START QUESTION #2 FUNCTIONS















