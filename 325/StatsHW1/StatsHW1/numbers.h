/**
	@file: numbers.h
	@author: Aleksandr Kibis
	@date: 12/7/2013
	@description: runs test cases on questions 1 and 2. 
*/

#include <string>
#include <iostream>
#include <random>

double* makeArray(int size, double lower, double upper);

int* intArray(int size, int lower, int upper);

double probMean(double* array, const int size, double lower, double upper);

double getMean(double* array, const int size);

double getIntMean(int* array, const int size);

double getSD(double* array, const int size);

