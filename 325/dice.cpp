/**
@File: dice.cpp
@Author: Aleksandr Kibis
@Date: 12/12/2013
*/

#include "dice.h"

using namespace std;

// Roll a single die
int rollDie(){
	random_device engine;
	// Define range of ints
	uniform_int_distribution<int> dist(1, 6);
	return dist(engine);
}

// Plays a single game of rolling two die
double* playGame(){

	// instantiate variables
	int rollCount = 0;
	bool cont = true;
	bool gameWon = false;
	double* results = new double[2];

	// create sum array with counter	
	int* countArray = new int[11];	
	for (int i=0; i<11; i++)
	countArray[i] = 0;

	// Play single game
	while (cont){

		// increment roll counter
		rollCount++;
		// roll two die
//		cout << "Roll count is: " << rollCount << endl;
		int first = rollDie();
//		cout << "First die: " << first << endl;
		int second = rollDie();
//		cout << "Second die: " << second << endl <<endl;
		
		// Determine outcome of first toss
		if (rollCount == 1){
			// if doubles, lose
			if (first == second){
//				cout << "Sorry, you lose. Please try again.\n";
				cont = false;
				break;
			}
		}
		if (first == second){
//		cout << "Sorry, you lose. Please try again.\n";
			cont = false;
			break;
		}
		// Get sum and increment sum counter by 1	
		int sum = first + second;
		countArray[sum - 2]++;
		// Check if particular sum has occured already
		if (countArray[sum - 2] > 1){
//			cout << "You win!" << endl;
			cont = false;
			gameWon = true;
		}
	}

	// populate game results array
	results[0] = rollCount;
//	cout << results[0] << endl;
	if (gameWon)
		results[1] = 1;
	else
		results[1] = 0;
//	cout << results[1] << endl;

	return results;
}

// Tests the die simulation for parts A and B
double* testGame(int simulations){
	double* testResults = new double[2];
	testResults[0] = 0;
	testResults[1] = 0;
	for (int i=0; i<simulations; i++){
		double* game = playGame();
		// populate first element with total roll count
		testResults[1] += game[0];
		// populate second element with total win count
		testResults[0] += game[1];
	}
	cout << "Number of wins: " << testResults[0] << endl;
	cout << "Number of rolls: " << testResults[1] << endl << endl;
	// A: probability of winning
	testResults[0] = testResults[0] / simulations;
	// B: expected number of tosses
	testResults[1] = testResults[1] / simulations;

	return testResults;
}