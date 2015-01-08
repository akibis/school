/**
	@file: numbers.cpp
	@author: Aleksandr Kibis
	@date: 12/7/2013
	@description: function implementation for test cases. 
*/

#include "numbers.h"
#include "math.h"

using namespace std;

// Make an array of random doubles
double* makeArray(int size, double lower, double upper)
{
	// create random distribution object betwen -1 and 1
	random_device engine;
	uniform_real_distribution<double> dist(lower, upper);
	double* myArray = new double[size];
	
	for (int i=0; i<size; i++)
	{
		// grab number from random distribution and assign as element of array
		double wubwub = dist(engine);
		myArray[i] = wubwub;
	}

	return myArray;
}

// Make array of random ints
int* intArray(int size, int lower, int upper)
{
	random_device engine;
	uniform_int_distribution<> dist(lower, upper);
	int* myArray = new int[size];
	for (int i=0; i < size; i++)
	{
		int dropTheBass = dist(engine);
		myArray[i] = dropTheBass;
	}
	return myArray;
}

// Get probability of mean (aka normal probability distribution)
double probMean(double* array, const int size, double lower, double upper)
{
	int count = 0;
	for (int i=0; i < size; i++)
	{
		if (0.0 <= array[i] <= 0.2)
			count++;
	}
	return count / (double)size;
}

// Get mean of an array of doubles
double getMean(double* array, const int size)
{
	double sum = 0;
	// sum elements of array
	for (int i=0; i < size; i++)
	{
		sum += array[i];
	}

	// sum/n
	return sum/size;
}

// Get mean of an array of ints
double getIntMean(int* array, const int size)
{
	double sum = 0;
	// sum elements of array
	for (int i=0; i < size; i++)
	{
		sum += array[i];
	}

	// sum/n
	return sum/size;
}

// Get standard deviation of array
double getSD(double* array, const int size)
{
	double sum = 0;

	// get mean
	double mean = getMean(array, size);

	for (int i=0; i < size; i++)
	{
		// check how far number is from mean
		double num = array[i];
		if (num < mean)
			num = -(mean - num);
		else
			num = num - mean;
		// square and add number to sum
		sum += (num*num);
	}
	// return square root of variance => standard deviation
	return sqrt(sum/size);
}
