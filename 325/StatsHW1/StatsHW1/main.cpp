/**
	@file: main.cpp
	@author: Aleksandr Kibis
	@date: 12/7/2013
	@description: runs test cases on questions 1 and 2. 
*/

#include "numbers.h"


using namespace std;

int main() {

	// Question #1
	cout << "************ Math 324 Homework #1 by Aleksandr Kibis **************\n\n\n";
	// Generate 225 samples of size 22500 random numbers from U(-1, 1). For each of these 225 samples calculate the mean. 
	cout << "########### QUESTION #1 ###########\n\n";
	cout << "Generating random samples...\n\n";

		//Find the simulated probability that the mean is between 0 and 0.2 inclusive. P(0 <= mean <= 0.2)


		double min = 0.0;
		double max = 0.2;


		//Find the mean of the means. Add 225 means together and divide by 225.
			
			// make an array which holds 225 means
			const int sampleSize = 225;
			const int arraySize = 22500;
			double* meanArray = new double[sampleSize];
			double meanSum = 0;
			for (int i=0; i < sampleSize; i++)
			{
				// fill meanArray using uniform random distribution object
				double* randomArray = makeArray(arraySize, -1.0, 1.0);
				meanArray[i] = getMean(randomArray, arraySize);

//UNCOMMENT TO PRINT MEAN ARRAY ELEMENTS		
//				cout << meanArray[i] << endl;

			}
			for (int i=0; i < sampleSize; i++)
			{
				meanSum += meanArray[i];
			}
			// Probability of mean
			cout << "The probability that the mean is between " << min << " and " << max << " is: ";
			cout << probMean(meanArray, sampleSize, min, max) << endl;

			// Mean of means
			cout << "The mean of means is: " << getMean(meanArray, sampleSize) << endl;

			// Standard Deviation of means
			cout << "The standard deviation of the means is: " << getSD(meanArray, sampleSize) << endl;

		//Draw the histogram of the means.


	// Question #2
	cout << "\n\n########### QUESTION #2 ###########\n\n";
	// Generate 225 samples of size 22500 random integers from the set {1, 2, 3, 4, 5, 6, 7, 8}. For each of these 225 samples calculate the mean. 
		double* meanOfIntsArray = new double[sampleSize];
			meanSum = 0;
			for (int i=0; i < sampleSize; i++)
			{
				// fill meanIntArray using uniform random distribution object
				int* randomIntArray = intArray(arraySize, 1, 8);
				meanOfIntsArray[i] = getIntMean(randomIntArray, arraySize);

//UNCOMMENT TO PRINT MEAN ARRAY ELEMENTS		
//				cout << meanOfIntsArray[i] << endl;

			}
			for (int i=0; i < sampleSize; i++)
			{
				meanSum += meanArray[i];
			}
		min = 3.8;
		max = 4.0;
		//Find the simulated probability that the mean is between 3.8 and 4.0 exclusive. P(3.8 < mean < 4.0)
		cout << "The probability that the mean is between " << min << " and " << max << " is: ";
		cout << probMean(meanOfIntsArray, sampleSize, min, max) << endl;
		
		//Find the simulated mean of the means.
		cout << "The mean of means is: " << getMean(meanOfIntsArray, sampleSize) << endl;

		//Find the simulated standard deviation of the means.
		cout << "The standard deviation of the means is: " << getSD(meanOfIntsArray, sampleSize) << endl;

		//Draw the histogram of the means.


	return 0;
}