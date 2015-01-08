/**
	Author: Aleksandr Kibis
	Date: 11/4/2013
	Project: HW6/func.cpp
**/

#include <iostream>
#include <string>

using namespace std;

// Write string backwards
string reverse(string input){
	string reversed = input;
	int size = input.length();
	for (int i=0; i<size; i++){
		reversed[i] = input[(size-1) - i];
	}
	return reversed;
}

// Given an array of n integers, find the largest integer
int findLargestInt(int &array){
//	int temp;
//	for (int i=0, i < array.length()
	return 1;
}

// Given an array of n integers and an integer k, find the k-th largest number

// Given an array of n integers, sort this array using the QuickSort algorithm