/**
@File: main.cpp
@Author: Aleksandr Kibis
@Date: 12/12/2013
*/

#include "uniformDist.h"
#include "dice.h"

using namespace std;

int main(){

	cout << "\n################### Math 324 Homework #2 - Aleksandr Kibis ###################\n\n";

	int simulations = 10000;
	cout << "*************** Question #1 ***************\n\n";

	cout << "Part A:\n";
	cout << "Building sample of size " << simulations << endl;
	double* myArrayA = buildSampleA(simulations);
	cout << getMean(simulations, myArrayA) << endl;

	cout << "\nPart B:\n";
	cout << "Building sample of size " << simulations << endl;
	double* myArrayB = buildSampleB(simulations);
	cout << getMean(simulations, myArrayB) << endl;


	cout << "*************** Question #2 ***************\n\n";

	cout << "Playing game " << simulations << " times" << endl;
	double* gameResults = testGame(simulations);
	
	cout << "Part A: probability of winning = " << gameResults[0] << endl;
	cout << "\nPart B: expected number of tosses per game = " << gameResults[1] << endl;


	return 0;
}