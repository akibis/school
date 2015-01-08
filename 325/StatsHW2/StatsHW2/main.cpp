/**
@File: main.cpp
@Author: Aleksandr Kibis
@Date: 12/12/2013
*/

#include "uniformDist.h"
#include "dice.h"

using namespace std;

int main(){

	cout << "*************** Question #1 ***************\n\n";

	cout << "Part A:\n";
	cout << "Building sample of size 10,000\n";
	double* myArrayA = buildSampleA(10000);
	cout << getMean(10000, myArrayA) << endl;

	cout << "\nPart B:\n";
	cout << "Building sample of size 10,000\n";
	double* myArrayB = buildSampleB(10000);
	cout << getMean(10000, myArrayB) << endl;


	cout << "*************** Question #2 ***************\n\n";

	int simulations = 100000;
	double* gameResults = testGame(simulations);
	
	cout << "Part A: probability of winning = " << gameResults[0] << endl;
	cout << "\nPart B: expected number of tosses per game = " << gameResults[1] << endl;


	return 0;
}